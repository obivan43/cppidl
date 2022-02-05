#pragma once

#include <vector>
#include <string>

namespace GoldParser
{
    //
    // Symbol Types
    //
    enum SymbolType
    {
        SymbolTypeNonterminal = 0,
        SymbolTypeTerminal = 1,
        SymbolTypeWhitespace = 2,
        SymbolTypeEnd = 3,
        SymbolTypeCommentStart = 4,
        SymbolTypeCommentEnd = 5,
        SymbolTypeCommentLine = 6,
        SymbolTypeError = 7
    };

    //
    // Initial Buffer Sizes
    //
    enum Constants
    {
        EEOF = 512,
        STACK_SIZE = 512,
        TOKEN_SIZE = 32,
        RT_BUFF_SIZE = 128,
        RT_INDEX_SIZE = 32,
        LEXEM_SIZE = 2048
    };

    //
    // Callback function prototypes
    //
    using _cbneedinput = void (*)(struct ParseInput* pconfig);

    struct SourceLocation {
        int m_Line;
        int m_Position;

        bool empty() const { return m_Line == 0 && m_Position == 0; }
    };

    struct Symbol
    {
        char* Name;
        short Type;
    };

    struct Rule
    {
        short NonTerminal;
        short* symbol;
        int nsymbol;
    };

    struct Edge
    {
        short CharSetIndex;
        short TargetIndex;
    };

    struct DfaState
    {
        char Accept;
        short AcceptIndex;
        Edge* edge;
        short nedge;
    };

    struct Action
    {
        short m_SymbolIndex;
        short m_Action;
        short m_Target;
    };

    struct LalrState
    {
        Action* m_Action;
        short naction;
    };

    struct Token
    {
        short id{};
        char* lexeme{};
        SourceLocation location;
        Token() = default;
        Token(const Token& other)
            : id(other.id)
            , location(other.location)
        {
            if (other.lexeme)
                lexeme = _strdup(other.lexeme);
        }
        Token& operator=(const Token& other)
        {
            if (this != &other)
            {
                id = other.id;
                location = other.location;
                if (other.lexeme)
                    lexeme = _strdup(other.lexeme);
            }
            return *this;
        }
        Token(Token&& other) noexcept
            : id(other.id)
            , lexeme(other.lexeme)
            , location(other.location)
        {
            other.lexeme = nullptr;
        }
        Token& operator=(Token&& other) noexcept
        {
            id = other.id;
            location = other.location;
            free(lexeme);
            lexeme = other.lexeme;
            other.lexeme = nullptr;
            return *this;
        }
        ~Token() { free(lexeme); }
    };

    struct StackElement
    {
        const Symbol* symbol;
        Token token;
        short state;
        short rule;
        // Reduction Tree
        short* rtchildren;
        short nrtchild;
        short rtchildofs;
        // End Reduction Tree
    };

    struct ParseInput
    {
        ParseInput() = default;
        ParseInput(const ParseInput& parseInput) = default;

        ~ParseInput()
        {
            if (inputFile)
                fclose(inputFile);
            free(buf);
        }

        struct Parser* parser{};
        char* buf{};
        int ncount{};
        int nofs{};
        int nbufsize{};
        _cbneedinput cbneedinput{};
        char bpreserve{};
        FILE* inputFile{};
    };

    // parser configuration
    struct ParseConfig
    {

        // create from memory
        ParseConfig(char* buffer, int len);
        explicit ParseConfig(const char* filename);
        ParseConfig(const ParseConfig& parseConfig) = delete;

        ~ParseConfig();
        void InitializeFromMemory(char* buffer, size_t len);

        short init_dfa{};
        short init_lalr{};
        char case_sensitive{};
        short start_symbol{};
        const char** charset{};
        short ncharset{};
        DfaState* dfa_state{};
        short ndfa_state{};
        Symbol* sym{};
        short nsym{};
        Rule* rule{};
        short nrule{};
        LalrState* lalr_state{};
        short nlalr_state{};
        static ParseConfig* instance;
    };

    //
    // Reduction Tree functions
    //

    struct ParserCallbacks
    {
        virtual void OnLineComment(const std::string& /*comment*/) {}
    };
    #define BUILD_RT

    // current parse info
    struct Parser
    {
        Parser();
        Parser(const Parser& parser);
        ~Parser();

        void OpenFile(const char* filename);
        short Parse();
        void Next();

        const char* GetChildLexeme(int index) const { return m_Stack[m_NStackOfs + index].token.lexeme; }
        SourceLocation GetChildLocation(int index) const { return m_Stack[m_NStackOfs + index].token.location; }
        int get_column() const { return m_Input.nofs - m_LastCharOfs; }

        //
        // Scan/Parse functions
        //

        // default scanner match function
        char def_matchtoken(short type);

        // check for eof on the input stream
        char get_eof();

        // get the next character from the input stream
        short get_char();

        // increment to next character in input stream
        void next_char();

        // get the next token
        short scan();

        void _push_token(short symbol, const char* lexeme = nullptr, SourceLocation location = {});
        void _pop_token();

        void _push_stack(short symValue, const Symbol* sym, short* rtIdx, short nrtIdx);
        void _pop_stack();

    #ifdef BUILD_RT
        // Reduction Tree
        short _push_rt_element(const StackElement& se);
        void _set_rt_head(const StackElement& se);
    #endif // BUILD_RT

        int m_CurrentLine{1};
        int m_CurrentPosition{1};
        int m_LastCharOfs{};
        ParserCallbacks* m_ParserCallbacks{};
        char m_Reduction{};
        short m_ReduceRule{};
        char m_Lexeme[LEXEM_SIZE]{};
        short m_Symbol{};
        short m_LalrState{};
        std::vector<StackElement> m_Stack{};
        short m_NStack{};
        short m_NStackSize{};
        size_t m_NStackOfs{};
        ParseInput m_Input;
        std::vector<Token> m_Tokens;

        // Reduction Tree
        std::vector<StackElement> m_Rt{};
        int m_RtSize{};
        int m_RtOfs{};
        // End Reduction Tree
    };

} // namespace GoldParser
