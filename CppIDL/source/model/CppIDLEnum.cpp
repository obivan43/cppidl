#include "CppIDLEnum.h"
#include "CppIDLFile.h"
#include "../utils/utils.h"

#include <iostream>

namespace cppidl {

	EnumEntry::EnumEntry(std::string_view name, Enum& info) : Element(ElementType::EnumEntry), m_Info(info), m_IsUserSpecified(false) {
		SetName(name);
	}

	Enum::Enum(std::string_view name) : Element(ElementType::Enum) {
		SetName(name);
	}

	bool Enum::AddEnumEntry(EnumEntry* enumEntry) {
		if (auto* prev = FirstOrNull(m_EnumEntries, ElementHasSameName, enumEntry->GetName())) {
			std::cerr << "Duplicated enum entry error" << std::endl;
			return false;
		}

		m_EnumEntries.push_back(enumEntry);
		return true;
	}

}
