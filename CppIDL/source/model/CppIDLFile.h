#pragma once

#include "CppIDLEnum.h"

#include <map>

namespace cppidl {

	typedef std::pair<int, Enum*> EnumConstant;

	class File {

		public:
			friend class cppidl::Enum;

		public:
			File() = default;
			File(std::string_view fileName);
			File(const File& other) = delete;

			const auto& GetEnums() const { return m_Enums; }
			std::string_view GetFileName() const { return m_FileName; }

			bool HasEnums() const { return !m_Enums.empty(); }

			bool AddEnum(Enum* enumInfo);
			void AddConstant(std::string_view name, cppidl::EnumConstant& enumConstant);

			bool FindConstant(std::string_view name, int& constantValue);

		private:
			std::string m_FileName;

			std::vector<cppidl::Enum*> m_Enums;
			std::map<std::string, cppidl::EnumConstant, std::less<>> m_EnumConstants;
	};

}
