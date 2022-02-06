#pragma once

#include "goldparser.h"

#include "../model/CppIDLEnum.h"
#include "../model/CppIDLFile.h"

#include <memory>

namespace cppidl {

	enum class CppIDLParserState {
		CppIDLParserState_Ok,
		CppIDLParserState_SyntaxError,
		CppIDLParserState_EnumError,
		CppIDLParserState_EnumEntryError
	};

	class CppIDLParser {

		public:
			CppIDLParser();

			CppIDLParserState Parse(const char* fileName);

		private:
			void CreateEnum(const char* name);
			void CreateEnumEntry(int value, bool isHex, bool userSpecified);
			void CreateEnumEntry(const Variant& value);
			void CreateEnumEntryInternal(EnumEntry* enumEntry);

			void Reset();

			void PrintEnums();

		private:
			Variant m_CurrentValue;
			CppIDLParserState m_ParserState;

			Enum* m_CurrentEnum;
			int m_NextEnumValue;
			std::vector<Enum*> m_ParsedEnums;

			File* m_CurrentFile;

			std::unique_ptr<GoldParser::ParseConfig> m_ParserConfig;
			std::unique_ptr<GoldParser::Parser> m_Parser;

	};

}
