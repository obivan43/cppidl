#pragma once

#include "CppIDLEnumEntry.h"

#include <vector>

namespace cppidl {

	class Enum : public Element {

		public:
			Enum(std::string_view name);

			const auto& GetEntries() const { return m_EnumEntries; }
			const EnumEntry& GetEntry(int index) const { return *m_EnumEntries[index]; }

			void SetEnumImplementationType(std::string_view type) { m_EnumImplementationType = type; }

			bool AddEnumEntry(EnumEntry* enumEntry);

		private:
			std::vector<EnumEntry*> m_EnumEntries;
			std::string m_EnumImplementationType;
	};

}
