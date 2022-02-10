#pragma once

#include "CppIDLEnumEntry.h"

#include <vector>

namespace cppidl {

	class Enum : public Element {

		public:
			Enum(std::string_view name);

			const auto& GetEntries() const { return m_EnumEntries; }
			const EnumEntry& GetEntry(int index) const { return *m_EnumEntries[index]; }
			bool GetIsEnumClass() const { return m_IsEnumClass; }

			void SetEnumImplementationType(std::string_view type) { m_EnumImplementationType = type; }
			void SetIsEnumClass(bool value) { m_IsEnumClass = value; }

			bool AddEnumEntry(EnumEntry* enumEntry);

		private:
			std::vector<EnumEntry*> m_EnumEntries;
			std::string m_EnumImplementationType;

			bool m_IsEnumClass;
	};

}
