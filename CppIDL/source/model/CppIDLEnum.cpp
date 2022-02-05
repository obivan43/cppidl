#include "CppIDLEnum.h"
#include "../utils/utils.h"

#include <iostream>

namespace cppidl {

	EnumEntry::EnumEntry(std::string_view name, Enum& info) : Element(ElementType::EnumEntry), m_Info(info), m_IsUserSpecified(false) {
		SetName(name);
	}

	Enum::Enum(std::string_view name) : Element(ElementType::Enum) {
		SetName(name);
	}

	void Enum::AddEnumEntry(EnumEntry* enumEntry) {
		static auto hasName = [](const Element* e, std::string_view name) { return e->GetName() == name; };

		if (auto* prev = FirstOrNull(m_EnumEntries, hasName, enumEntry->GetName())) {
			std::cerr << "Duplicated enum entry" << std::endl;
			return;
		}

		m_EnumEntries.push_back(enumEntry);
	}

}
