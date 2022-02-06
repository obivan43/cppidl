#include "cppidlparser.h"
#include "cppidl_enum.cpp"

#include <iostream>
#include <cassert>

namespace cppidl {

	CppIDLParser::CppIDLParser() : m_ParserState(CppIDLParserState::CppIDLParserState_Ok), m_CurrentEnum(nullptr), m_NextEnumValue(0) {
		m_ParserConfig = std::make_unique<GoldParser::ParseConfig>("data/cppidl_enum.cgt");
		m_Parser = std::make_unique<GoldParser::Parser>();
	}

	CppIDLParserState CppIDLParser::Parse(const char* fileName) {
		m_ParserState = CppIDLParserState::CppIDLParserState_Ok;
		m_CurrentFile = new File(fileName);

		m_Parser->OpenFile(fileName);
		while (true) {
			short res = m_Parser->Parse();

			if (res == SYM_FILE)
				continue;

			if (res == SYM_EOF) 
				break;

			if (res == -1) {
				Reset();

				m_ParserState = CppIDLParserState::CppIDLParserState_SyntaxError;
				std::cerr << "Syntax error" << '\n';
				break;
			}

			switch (m_Parser->m_ReduceRule)
			{

			case PROD_ENUMDECLARATIONIDENTIFIER_IDENTIFIER:
				CreateEnum(m_Parser->GetChildLexeme(1));
				break;
			case PROD_ENUMTYPESPECIFICATION_COLON:
				m_CurrentEnum->SetEnumImplementationType(m_Parser->GetChildLexeme(1));
				break;
			case PROD_ENUMDECLARATION_ENUM_LBRACE_RBRACE:
				assert(m_CurrentEnum);
				m_ParsedEnums.push_back(m_CurrentEnum);
				m_NextEnumValue = 0;
				m_CurrentEnum = nullptr;
				break;
			case PROD_ENUMVALUE_IDENTIFIER:
				CreateEnumEntry(m_NextEnumValue, false, false);
				break;
			case PROD_ENUMVALUE_IDENTIFIER_EQ:
				CreateEnumEntry(m_CurrentValue.GetInt(), m_CurrentValue.GetWasHexa(), true);
				m_CurrentValue.Clear();
				break;
			case PROD_ENUMVALUE_IDENTIFIER_EQ2:
				CreateEnumEntry(m_NextEnumValue, false, true);
				break;
			case PROD_ENUMVALUE_IDENTIFIER_EQ3:
				CreateEnumEntry(m_CurrentValue);
				m_CurrentValue.Clear();
				break;
			case PROD_ENUMCOMBINAISON:
				m_NextEnumValue = m_CurrentValue.GetInt();
				m_CurrentValue.Clear();
				break;
			case PROD_ENUMCOMBINAISON_PIPE:
				m_NextEnumValue |= m_CurrentValue.GetInt();
				m_CurrentValue.Clear();
				break;
			case PROD_ENUMCOMBINAISON_PLUS:
				m_NextEnumValue += m_CurrentValue.GetInt();
				m_CurrentValue.Clear();
				break;

			case PROD_SIGNEDNUMBER:
				break;
			case PROD_SIGNEDNUMBER_MINUS:
				m_CurrentValue.SetUnsignedInt(static_cast<unsigned>(_atoi64(m_Parser->GetChildLexeme(1))));
				m_CurrentValue.SetInt(-static_cast<int>(m_CurrentValue.GetUnsignedInt()));
				break;
			case PROD_UNSIGNEDNUMBER_DECNUMBER:
				m_CurrentValue.SetUnsignedInt(static_cast<unsigned>(_atoi64(m_Parser->GetChildLexeme(0))));
				break;
			case PROD_UNSIGNEDNUMBER_HEXNUMBER:
				m_CurrentValue.SetHexInt(m_Parser->GetChildLexeme(0));
				break;

			default:
				break;
			}

			if (m_ParserState != CppIDLParserState::CppIDLParserState_Ok) {
				Reset();
				break;
			}

			m_Parser->Next();
		}

		if (m_ParserState == CppIDLParserState::CppIDLParserState_Ok) {
			PrintEnums();
		}

		return m_ParserState;
	}

	void CppIDLParser::CreateEnum(const char* name) {
		std::string enumName(name);

		assert(!enumName.empty());
		assert(m_CurrentFile);

		m_CurrentEnum = new Enum(enumName);

		if (!m_CurrentFile->AddEnum(m_CurrentEnum)) {
			m_ParserState = CppIDLParserState::CppIDLParserState_EnumError;
		}
	}

	void CppIDLParser::CreateEnumEntry(int value, bool isHex, bool userSpecified) {
		EnumEntry* enumEntry = new EnumEntry(m_Parser->GetChildLexeme(1), *m_CurrentEnum);

		Variant var;
		var.SetInt(value);
		var.SetWasHexa(isHex);

		enumEntry->SetValue(var);
		enumEntry->SetIsUserSpecified(userSpecified);

		CreateEnumEntryInternal(enumEntry);
	}

	void CppIDLParser::CreateEnumEntry(const Variant& value) {
		EnumEntry* enumEntry = new EnumEntry(m_Parser->GetChildLexeme(1), *m_CurrentEnum);

		enumEntry->SetValue(value);

		CreateEnumEntryInternal(enumEntry);
	}

	void CppIDLParser::CreateEnumEntryInternal(EnumEntry* enumEntry) {
		assert(m_CurrentEnum);

		if (!m_CurrentEnum->AddEnumEntry(enumEntry)) {
			m_ParserState = CppIDLParserState::CppIDLParserState_EnumEntryError;
			delete enumEntry;
			return;
		}

		EnumConstant enumConstant{ enumEntry->GetValue().GetInt(), m_CurrentEnum };
		m_CurrentFile->AddConstant(enumEntry->GetName(), enumConstant);

		m_NextEnumValue = enumEntry->GetValue().GetInt() + 1;
	}

	void CppIDLParser::PrintEnums() {
		for (Enum* parsedEnum : m_ParsedEnums) {
			std::cout << parsedEnum->GetName() << '\n';
			for (EnumEntry* enumEntry : parsedEnum->GetEntries()) {
				std::cout << enumEntry->GetName() << " = " << enumEntry->GetValue() << '\n';
			}
		}
	}

	void CppIDLParser::Reset() {
		m_CurrentValue = Variant();
		m_NextEnumValue = 0;

		if (m_CurrentEnum)
			delete m_CurrentEnum;

		if (m_CurrentFile)
			delete m_CurrentFile;
		
		m_ParsedEnums.clear();
	}

}
