#pragma once

#include <string>

namespace cppidl {

	enum class ElementType {
		Enum,
		EnumEntry,
		Count
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

}