#include "CppIDLEnum.h"
#include "CppIDLFile.h"
#include "../utils/utils.h"

#include <iostream>

namespace cppidl {

	EnumEntry::EnumEntry(std::string_view name, Enum& info) : Element(ElementType::EnumEntry), m_Info(info), m_IsUserSpecified(false) {
		SetName(name);
	}

	Enum::Enum(std::string_view name, cppidl::File* file) : Element(ElementType::Enum) {
		SetName(name);

		if(file != nullptr)
			file->m_Enums.push_back(this);
	}

	bool Enum::AddEnumEntry(EnumEntry* enumEntry) {
		static auto hasName = [](const Element* e, std::string_view name) { return e->GetName() == name; };

		if (auto* prev = FirstOrNull(m_EnumEntries, hasName, enumEntry->GetName())) {
			std::cerr << "Duplicated enum entry" << std::endl;
			return false;
		}

		m_EnumEntries.push_back(enumEntry);
		return true;
	}

}
