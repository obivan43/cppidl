#pragma once

#include <string>

namespace cppidl {

	enum class ElementType {
		ElementType_Enum,
		ElementType_EnumEntry,
		ElementType_Count
	};

	class Element {

		public:
			explicit Element(ElementType type);
			Element(const Element& other) = default;

			virtual ~Element() = default;

			ElementType GetType() const { return m_Type; }
			std::string_view GetName() const { return m_Name; }

			void SetName(std::string_view name) { m_Name = name; }

		private:
			ElementType m_Type;
			std::string m_Name;
	};

	static bool ElementHasSameName(const Element* e, std::string_view name) { return e->GetName() == name; };

}
