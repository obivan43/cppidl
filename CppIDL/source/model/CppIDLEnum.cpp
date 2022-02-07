#include "CppIDLEnum.h"
#include "../utils/utils.h"

#include <iostream>

namespace cppidl {

	Enum::Enum(std::string_view name) : Element(ElementType::ElementType_Enum) {
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
