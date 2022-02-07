#pragma once

#include "CppIDLVariant.h"
#include "CppIDLElement.h"

namespace cppidl {

	class Enum;

	class EnumEntry : public Element {

	public:
		EnumEntry(std::string_view name, Enum& info);

		const Variant& GetValue() const { return m_Value; }
		bool GetIsUserSpecified() const { return m_IsUserSpecified; }

		void SetValue(const Variant& value) { m_Value = value; }
		void SetIsUserSpecified(bool value) { m_IsUserSpecified = value; }

	private:
		Enum& m_Info;
		Variant m_Value;
		bool m_IsUserSpecified;
	};

}
