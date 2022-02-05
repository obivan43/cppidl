#pragma once

#include "CppIDLVariant.h"
#include "CppIDLElement.h"

#include <vector>
#include <utility>

namespace cppidl {

	class Enum;
	class File;

	typedef std::pair<int, Enum*> EnumConstant;

	class EnumEntry : public Element {

		public:
			EnumEntry(std::string_view name, Enum& info);

			const Variant& GetValue() const { return m_Value; }
			bool GetIsUserSpecified() const { return m_IsUserSpecified; }

			void SetValue(const Variant& value) { m_Value = value; }
			void SetIsUserSpecified(bool value) { m_IsUserSpecified = value; }

		private:
			Enum& m_Info;
			Variant m_Value;
			bool m_IsUserSpecified;
	};

	class Enum : public Element {

		public:
			Enum(std::string_view name, cppidl::File* file);

			const auto& GetEntries() const { return m_EnumEntries; }
			const EnumEntry& GetEntry(int index) const { return *m_EnumEntries[index]; }

			void SetEnumImplementationType(std::string_view type) { m_EnumImplementationType = type; }

			bool AddEnumEntry(EnumEntry* enumEntry);

		private:
			std::vector<EnumEntry*> m_EnumEntries;
			std::string m_EnumImplementationType;
	};

}
