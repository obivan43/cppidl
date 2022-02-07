#include "CppIDLEnumEntry.h"

namespace cppidl {

	EnumEntry::EnumEntry(std::string_view name, Enum& info) : Element(ElementType::ElementType_EnumEntry), m_Info(info), m_IsUserSpecified(false) {
		SetName(name);
	}

}