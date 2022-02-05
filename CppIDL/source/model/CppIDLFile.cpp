#include "CppIDLFile.h"

namespace cppidl {

	File::File(std::string_view fileName) : m_FileName(fileName) {}

	void File::AddConstant(std::string_view name, cppidl::EnumConstant& enumConstant) {
		std::string constantName{ enumConstant.second->GetName() };
		constantName += "::";
		constantName += name;

		m_EnumConstants[constantName] = enumConstant;
	}

}
