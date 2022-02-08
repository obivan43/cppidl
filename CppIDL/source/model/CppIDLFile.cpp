#include "CppIDLFile.h"

#include "../utils/utils.h"

namespace cppidl {

	File::File(std::string_view fileName) : m_FileName(fileName) {}

	bool File::AddEnum(Enum* enumInfo) {
		if (auto* prev = FirstOrNull(m_Enums, ElementHasSameName, enumInfo->GetName())) {
			std::cerr << "Duplicated enum error" << std::endl;
			return false;
		}

		m_Enums.push_back(enumInfo);
		return true;
	}
	
	void File::AddConstant(std::string_view name, cppidl::EnumConstant& enumConstant) {
		std::string constantName{ enumConstant.second->GetName() };
		constantName += "::";
		constantName += name;

		m_EnumConstants[constantName] = enumConstant;
	}

	bool File::FindConstant(std::string_view name, int& constantValue) {
		auto it = m_EnumConstants.find(name);
		bool isFound = (it != m_EnumConstants.end());
		
		if (isFound) {
			constantValue = it->second.first;
		}

		return isFound;
	}

}
