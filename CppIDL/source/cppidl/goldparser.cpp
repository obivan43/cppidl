#include "goldparser.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

#include <io.h>

namespace GoldParser
{
    #define ActionShift 1
    #define ActionReduce 2
    #define ActionGoto 3
    #define ActionAccept 4
    char Parser::def_matchtoken(short type)
    {
        short c;
        switch (type)
        {
        case SymbolTypeCommentStart:
            while ((c = get_char()) != EEOF)
            {
                if (c == '*')
                {
                    next_char();
                    c = get_char();
                    if (c != EEOF)
                    {
                        if (c == '/')
                        {
                            next_char();
                            return 0;
                        }
                    }
                }
                next_char();
            }
            m_Symbol = 0;
            return 0;
        case SymbolTypeCommentLine:
        {
            std::ostringstream currentLineComment;
            currentLineComment << "//";
            while ((c = get_char()) != EEOF)
            {
                if (c == '\r')
                {
                    next_char();
                    if ((c = get_char()) == '\n')
                    {
                        next_char();
                        currentLineComment << static_cast<char>(c);
                        if (m_ParserCallbacks)
                            m_ParserCallbacks->OnLineComment(currentLineComment.str());
                        return 0;
                    }
                    return 0;
                }
                if (c == '\n')
                {
                    next_char();
                    currentLineComment << static_cast<char>(c);
                    if (m_ParserCallbacks)
                        m_ParserCallbacks->OnLineComment(currentLineComment.str());
                    return 0;
                }
                currentLineComment << static_cast<char>(c);
                next_char();
            }
            m_Symbol = 0;
            if (m_ParserCallbacks)
                m_ParserCallbacks->OnLineComment(currentLineComment.str());
            return 0;
        }
        case SymbolTypeWhitespace:
            return 0;
        default:
            return 1;
        }
    }
    char Parser::get_eof()
    {
        struct ParseInput* pinput = &m_Input;
        if (pinput->nofs >= pinput->ncount && pinput->cbneedinput)
            pinput->cbneedinput(pinput);
        return (pinput->nofs >= pinput->ncount) ? 1 : 0;
    }
    short Parser::get_char()
    {
        if (m_Input.buf[m_Input.nofs] == '\n'
    #ifdef _WIN32
            && m_LastCharOfs != m_Input.nofs
    #endif
        )
        {
            ++m_CurrentLine;
            m_LastCharOfs = m_Input.nofs;
        }
        return get_eof() ? EEOF : m_Input.buf[m_Input.nofs];
    }
    void Parser::next_char()
    {
        if (m_Input.nofs < m_Input.ncount)
            m_Input.nofs++;
    }
    short Parser::scan()
    {
        const ParseConfig* pconfig = ParseConfig::instance;
        struct DfaState* dfa = &ParseConfig::instance->dfa_state[ParseConfig::instance->init_dfa];
        struct ParseInput* pinput = &m_Input;
        short last_accepted{-1};
        int last_accepted_size{};
        char* lexeme = m_Lexeme;
        m_Lexeme[0] = 0;
        int start_ofs = pinput->nofs;
        m_Input.bpreserve = 0;
        if (get_eof())
            return 0;
        int i = 0;
        short nedge = 0;
        short idx;
        short c;

        while (true)
        {
            m_Input.bpreserve = (last_accepted == -1) ? 0 : 1;
            c = get_char();
            m_Input.bpreserve = 0;
            if (!pconfig->case_sensitive && c != EEOF)
                c = static_cast<short>(tolower(c));
            if (c != EEOF)
            {
                nedge = dfa->nedge;
                for (i = 0; i < nedge; i++)
                {
                    idx = dfa->edge[i].CharSetIndex;
                    if (strchr(pconfig->charset[idx], c))
                    {
                        dfa = &pconfig->dfa_state[dfa->edge[i].TargetIndex];
                        *lexeme++ = static_cast<char>(c);
                        if (dfa->Accept)
                        {
                            last_accepted = dfa->AcceptIndex;
                            last_accepted_size = (pinput->nofs - start_ofs) + 1;
                        }
                        break;
                    }
                }
            }
            if ((c == EEOF) || (i == nedge))
            {
                if (last_accepted != -1)
                {
                    m_Lexeme[last_accepted_size] = 0;
                    if (short index = dfa->AcceptIndex; index != -1)
                    {
                        if (!def_matchtoken(pconfig->sym[index].Type))
                        {
                            lexeme = m_Lexeme;
                            lexeme[0] = 0;
                            if (c == EEOF || (last_accepted == -1))
                                return 0;
                            dfa = &pconfig->dfa_state[pconfig->init_dfa];
                            last_accepted = -1;
                            start_ofs = m_Input.nofs;
                            continue;
                        }
                    }
                }
                break;
            }
            next_char();
        }
        if (last_accepted == -1)
        {
            lexeme = m_Lexeme;
            lexeme[0] = 0;
            if (get_eof())
                return 0;
            return -1;
        }
        m_CurrentPosition = m_Input.nofs - last_accepted_size;
        return last_accepted;
    }
    Parser::Parser()
    {
        m_NStackSize = STACK_SIZE;
        m_Stack.resize(STACK_SIZE);
        m_LalrState = ParseConfig::instance->init_lalr;
        m_Lexeme[0] = '\0';
        m_Input.parser = this;
        m_Tokens.reserve(TOKEN_SIZE);
        m_RtOfs = 1;
        m_RtSize = RT_BUFF_SIZE;
        m_Rt.resize(m_RtSize);
    }
    Parser::~Parser()
    {
        while (!m_Tokens.empty())
            _pop_token();
        for (int i = 0; i < m_RtOfs; ++i)
        {
            if (m_Rt[i].rtchildren)
                free(m_Rt[i].rtchildren);
        }
    }

    

    ParseConfig::ParseConfig(const char* filename)
    {
        instance = this;
        char* buf;
        if ((_access(filename, 0)) != 0)
        {
            std::cerr << "File doesn't exist: " << filename;
            return;
        }

        FILE* fin = fopen(filename, "rb");
        if (!fin)
        {
            perror("fopen() ");
            std::cerr << "Can't open file: " << filename;
            return;
        }

        std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
        size_t fileSize = static_cast<size_t>(in.tellg());
        buf = (char*)malloc(fileSize);
        if (!buf)
        {
            fclose(fin);
            std::cerr << "Can't read file: " << filename;
            return;
        }
        [[maybe_unused]] size_t read = fread(buf, fileSize, 1, fin);
        fclose(fin);
        InitializeFromMemory(buf, fileSize);
        free(buf);
    }

    short Parser::_push_rt_element(const StackElement& se)
    {
        if (m_RtOfs >= m_RtSize)
        {
            m_RtSize += RT_BUFF_SIZE;
            m_Rt.resize(m_RtSize);
        }
        m_Rt[m_RtOfs] = se;
        if (se.rtchildren)
        {
            m_Rt[m_RtOfs].rtchildren = (short*)malloc(sizeof(short) * se.rtchildofs);
            memcpy((void*)m_Rt[m_RtOfs].rtchildren, se.rtchildren, sizeof(short) * se.rtchildofs);
            m_Rt[m_RtOfs].nrtchild = se.nrtchild;
            m_Rt[m_RtOfs].rtchildofs = se.rtchildofs;
        }
        m_RtOfs++;
        return static_cast<short>(m_RtOfs - 1);
    }

    void Parser::_set_rt_head(const StackElement& se)
    {
        auto& rt = m_Rt[0];
        if (rt.rtchildren)
            free(rt.rtchildren);
        rt.symbol = se.symbol;
        rt.token = se.token;
        rt.rule = se.rule;
        rt.state = se.state;
        if (se.token.lexeme)
            rt.token.lexeme = _strdup(se.token.lexeme);
        if (se.rtchildren)
        {
            rt.rtchildren = (short*)malloc(sizeof(short) * se.rtchildofs);
            memcpy((void*)rt.rtchildren, (const void*)se.rtchildren, sizeof(short) * se.rtchildofs);
            rt.nrtchild = se.nrtchild;
            rt.rtchildofs = se.rtchildofs;
        }
        else
        {
            rt.rtchildren = nullptr;
            rt.nrtchild = 0;
            rt.rtchildofs = 0;
        }
    }
    char* getws(char* b, char* s)
    {
        while (b && (*b || *(b + 1)))
        {
            *s++ = *b;
            b += 2;
        }
        if (b)
            *s++ = *b;
        b += 2;
        return b;
    }
    char* getsh(char* b, short* s)
    {
        auto* _b = (unsigned char*)b;
        *s = *_b++;
        *s |= (*_b++) << 8;
        return (char*)_b;
    }
    char* getvws(char* b, char* str)
    {
        assert(*b == 'S');
        b++;
        return getws(b, str);
    }
    char* skipvws(char* b)
    {
        b++;
        while (*b++)
            b++;
        return ++b;
    }
    char* getvb(char* b, unsigned char* v)
    {
        b++;
        *v = *(unsigned char*)b++;
        return b;
    }
    char* getvsh(char* b, short* v)
    {
        b++;
        return getsh(b, v);
    }

    ParseConfig::ParseConfig(char* b, int len)
    {
        instance = this;
        InitializeFromMemory(b, len);
    }
    void ParseConfig::InitializeFromMemory(char* b, size_t len)
    {
        char str[1024];
        ParseConfig* res = this;
        char* bend;
        short nEntries;
        unsigned char recType;
        short idx;
        unsigned char byt;
        int i;

        if (!b || !len)
        {
            std::cerr << "Can't read buffer";
            return;
        }

        bend = b + len;
        b = getws(b, str);
        if (strcmp(str, "GOLD Parser Tables/v1.0"))
            std::cerr << "Can't read buffer; old tables";
        std::vector<unsigned char> recTypeDebugStack;
        while (b < bend)
        {
            b++;
            b = getsh(b, &nEntries);
            b = getvb(b, &recType);

            recTypeDebugStack.push_back(recType);
            switch (recType)
            {
            case 'P':
                b = skipvws(b);
                b = skipvws(b);
                b = skipvws(b);
                b = skipvws(b);
                b = getvb(b, &byt);
                b = getvsh(b, &res->start_symbol);
                res->case_sensitive = byt ? 1 : 0;
                break;
            case 'T':
            {
                b = getvsh(b, &res->nsym);
                b = getvsh(b, &res->ncharset);
                b = getvsh(b, &res->nrule);
                b = getvsh(b, &res->ndfa_state);
                b = getvsh(b, &res->nlalr_state);
                res->charset = (const char**)malloc(sizeof(char*) * res->ncharset);
                res->dfa_state = (struct DfaState*)malloc(sizeof(struct DfaState) * res->ndfa_state);
                res->sym = (struct Symbol*)malloc(sizeof(struct Symbol) * res->nsym);
                res->rule = (struct Rule*)malloc(sizeof(struct Rule) * res->nrule);
                res->lalr_state = (struct LalrState*)malloc(sizeof(struct LalrState) * res->nlalr_state);
            }
            break;
            case 'I':
                b = getvsh(b, &res->init_dfa);
                b = getvsh(b, &res->init_lalr);
                break;
            case 'S':
            {
                b = getvsh(b, &idx);
                b = getvws(b, str);
                b = getvsh(b, &res->sym[idx].Type);
                res->sym[idx].Name = _strdup(str);
            }
            break;
            case 'C':
            {
                b = getvsh(b, &idx);
                b = getvws(b, str);
                res->charset[idx] = _strdup(str);
            }
            break;
            case 'R':
                b = getvsh(b, &idx);
                b = getvsh(b, &res->rule[idx].NonTerminal);
                b++;
                res->rule[idx].nsymbol = nEntries - 4;
                res->rule[idx].symbol = (short*)malloc(sizeof(short) * (nEntries - 4));
                for (i = 0; i < nEntries - 4; i++)
                    b = getvsh(b, &res->rule[idx].symbol[i]);
                break;
            case 'D':
                b = getvsh(b, &idx);
                b = getvb(b, &byt);
                b = getvsh(b, &res->dfa_state[idx].AcceptIndex);
                res->dfa_state[idx].Accept = byt ? 1 : 0;
                b++;
                res->dfa_state[idx].nedge = (nEntries - 5) / 3;
                res->dfa_state[idx].edge = (struct Edge*)malloc(sizeof(struct Edge) * ((nEntries - 5) / 3));
                for (i = 0; i < nEntries - 5; i += 3)
                {
                    b = getvsh(b, &res->dfa_state[idx].edge[i / 3].CharSetIndex);
                    b = getvsh(b, &res->dfa_state[idx].edge[i / 3].TargetIndex);
                    b++;
                }
                break;
            case 'L':
                b = getvsh(b, &idx);
                b++;
                res->lalr_state[idx].naction = (nEntries - 3) / 4;
                res->lalr_state[idx].m_Action = (struct Action*)malloc(sizeof(struct Action) * ((nEntries - 3) / 4));
                for (i = 0; i < nEntries - 3; i += 4)
                {
                    b = getvsh(b, &res->lalr_state[idx].m_Action[i / 4].m_SymbolIndex);
                    b = getvsh(b, &res->lalr_state[idx].m_Action[i / 4].m_Action);
                    b = getvsh(b, &res->lalr_state[idx].m_Action[i / 4].m_Target);
                    b++;
                }
                break;

            default:
                std::cerr << "Unknown record";
            }
        }
    }
    ParseConfig* ParseConfig::instance;

    ParseConfig::~ParseConfig()
    {
        int i;
        for (i = 0; i < ncharset; i++)
            free((void*)charset[i]);
        for (i = 0; i < nrule; i++)
            free(rule[i].symbol);
        for (i = 0; i < ndfa_state; i++)
            free(dfa_state[i].edge);
        for (i = 0; i < nlalr_state; i++)
            free(lalr_state[i].m_Action);
        for (i = 0; i < nsym; i++)
            free(sym[i].Name);
        free((char**)charset);
        free(dfa_state);
        free(sym);
        free(rule);
        free(lalr_state);
        instance = nullptr;
    }
    void Parser::_pop_stack()
    {
        if (m_NStack < 1)
            return;
        m_NStack--;
        auto& top = m_Stack[m_NStack];
        if (top.token.lexeme)
        {
            free(top.token.lexeme);
            top.token.lexeme = nullptr;
        }
        if (top.rtchildren)
        {
            free(top.rtchildren);
            top.nrtchild = 0;
            top.rtchildofs = 0;
        }
    }
    void Parser::_push_stack(short symValue, const Symbol* sym, short* rtIdx, short nrtIdx)
    {
        if ((m_NStack + 1) >= m_NStackSize)
        {
            m_NStackSize += STACK_SIZE;
            m_Stack.resize(m_NStackSize);
        }
        StackElement& se = m_Stack[m_NStack++];
        se.symbol = sym;
        se.token.id = symValue;
        se.token.lexeme = _strdup(m_Lexeme);
        se.token.location = {m_CurrentLine, m_CurrentPosition};
        se.state = m_LalrState;
        se.rule = m_ReduceRule;

        se.nrtchild = 0;
        se.rtchildren = nullptr;
        se.rtchildofs = 0;
        if (rtIdx && nrtIdx)
        {
            se.rtchildren = rtIdx;
            se.nrtchild = nrtIdx;
            se.rtchildofs = nrtIdx;
        }
    }
    void Parser::_push_token(short symbol, const char* lexeme, SourceLocation location)
    {
        m_Tokens.resize(m_Tokens.size() + 1);
        m_Tokens.back().id = symbol;
        m_Tokens.back().lexeme = lexeme ? _strdup(lexeme) : nullptr;
        m_Tokens.back().location = location;
    }
    void Parser::_pop_token()
    {
        if (m_Tokens.empty())
            return;
        m_Tokens.pop_back();
    }
    void cbgetinput(ParseInput* pinput)
    {
        if (pinput->ncount == 0)
        {
            int nr = static_cast<int>(fread(pinput->buf, 1, pinput->nbufsize, pinput->inputFile));
            pinput->nofs = 0;
            pinput->ncount = nr;
        }
    }

    void Parser::OpenFile(const char* filename)
    {
        m_Input.inputFile = fopen(filename, "rb");
        if (!m_Input.inputFile)
        {
            std::cerr << "Cannot open file " << filename;
            return;
        }
        fseek(m_Input.inputFile, 0, SEEK_END);
        m_Input.nbufsize = ftell(m_Input.inputFile);
        fseek(m_Input.inputFile, 0, SEEK_SET);
        m_Input.buf = (char*)malloc(m_Input.nbufsize + 1);
        m_Input.cbneedinput = cbgetinput;

        int nr = static_cast<int>(fread(m_Input.buf, 1, m_Input.nbufsize, m_Input.inputFile));
        m_Input.nofs = 0;
        m_Input.ncount = nr;

        m_Input.buf[m_Input.nbufsize] = 0;
    }

    short Parser::Parse()
    {
        int i;
        char bfound;

        if (m_Reduction)
        {
            const Symbol* sym{};
            struct Rule* rule = &ParseConfig::instance->rule[m_ReduceRule];
            short* rtIdx = nullptr;
            int nrtIdx = 0;

            m_Symbol = rule->NonTerminal;
            _push_token(m_Symbol);

            if (rule->nsymbol)
            {
                nrtIdx = rule->nsymbol;
                rtIdx = (short*)malloc(sizeof(short) * nrtIdx);
                for (i = 0; i < rule->nsymbol; i++)
                {
                    rtIdx[i] = _push_rt_element(m_Stack[m_NStack - 1]);
                    _pop_stack();
                }
                m_LalrState = m_Stack[m_NStack].state;
            }
            if (m_Symbol < ParseConfig::instance->nsym)
                sym = &ParseConfig::instance->sym[m_Symbol];
            _push_stack(rule->NonTerminal, sym, rtIdx, static_cast<short>(nrtIdx));

            _set_rt_head(m_Stack[m_NStack - 1]);

            m_Reduction = 0;
        }

        while (true)
        {
            if (m_Tokens.empty())
            {
                if ((m_Symbol = scan()) < 0)
                    return -1;
                _push_token(m_Symbol, m_Lexeme, {m_CurrentLine, m_CurrentPosition});
            }
            else
            {
                m_Symbol = m_Tokens.back().id;
                if (m_Tokens.back().lexeme)
                {
    #ifdef _WIN32
                    strncpy_s(m_Lexeme, LEXEM_SIZE, m_Tokens.back().lexeme, LEXEM_SIZE - 1);
    #else
                    strncpy(m_Lexeme, m_Tokens.back().lexeme, LEXEM_SIZE - 1);
    #endif
                    m_CurrentPosition = m_Tokens.back().location.m_Position;
                    m_CurrentLine = m_Tokens.back().location.m_Line;
                }
            }

            bfound = 0;
            for (i = 0; (!bfound) && (i < ParseConfig::instance->lalr_state[m_LalrState].naction); i++)
            {
                struct Action* action = &ParseConfig::instance->lalr_state[m_LalrState].m_Action[i];
                if (action->m_SymbolIndex == m_Symbol)
                {
                    bfound = 1;
                    switch (action->m_Action)
                    {
                    case ActionShift:
                    {
                        const Symbol* sym{};
                        if (m_Symbol < ParseConfig::instance->nsym)
                            sym = &ParseConfig::instance->sym[m_Symbol];
                        _push_stack(m_Symbol, sym, nullptr, 0);

                        m_NStackOfs = m_NStack - 1;
                        m_LalrState = action->m_Target;
                        _pop_token();
                    }
                    break;

                    case ActionReduce:
                    {
                        struct Rule* rule = &ParseConfig::instance->rule[action->m_Target];
                        m_Lexeme[0] = '\0';
                        m_ReduceRule = action->m_Target;
                        m_NStackOfs = m_NStack - rule->nsymbol;
                        m_Reduction = 1;
                        return rule->NonTerminal;
                    }

                    case ActionGoto:
                        m_LalrState = action->m_Target;
                        _pop_token();
                        break;

                    case ActionAccept:
                        return 0;
                    default:
                        break;

                    }
                }
            }
            if (!bfound)
            {
                if (m_Symbol)
                    break;
                return 0;
            }
        }
        return -1;
    }

    void Parser::Next()
    {
        const char* lexeme = GetChildLexeme(0);
        if (lexeme)
        {
    #ifdef _WIN32
            strncpy_s(m_Lexeme, LEXEM_SIZE, lexeme, LEXEM_SIZE - 1);
    #else
            strncpy(m_Lexeme, lexeme, LEXEM_SIZE - 1);
    #endif
            m_CurrentPosition = GetChildLocation(0).m_Position;
            m_CurrentLine = GetChildLocation(0).m_Line;
        }
    }

}
