#pragma once

#include "CppIDLVariant.h"
#include "CppIDLElement.h"

#include <vector>

namespace cppidl {

	class Enum;

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
			Enum(std::string_view name);

			const auto& GetEntries() const { return m_EnumEntries; }
			int GetEntriesAmount() const { return m_EnumEntries.size(); }
			const EnumEntry& GetEntry(int index) const { return *m_EnumEntries[index]; }

			void SetEnumImplementationType(std::string_view type) { m_EnumImplementationType = type; }

			void AddEnumEntry(EnumEntry* enumEntry);

		private:
			std::vector<EnumEntry*> m_EnumEntries;
			std::string m_EnumImplementationType;
	};

}
