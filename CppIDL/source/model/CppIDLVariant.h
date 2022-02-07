#pragma once

#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <iostream>

namespace cppidl {

	enum class VariantType {
		VariantType_EmptyType,
		VariantType_IntType,
		VariantType_UnsignedInt64Type,
		VariantType_Count
	};

	class Variant {

		public:
			Variant() = default;

			bool IsEmpty() const { return m_Type == VariantType::VariantType_EmptyType; }
			bool IsInt() const { return m_Type == VariantType::VariantType_IntType; }

			VariantType GetType() const { return m_Type; }
			bool GetIsSigned() const { return m_IsSigned; }
			bool GetWasHexa() const { return m_WasIntHexa; }

			int GetInt() const;
			unsigned int GetUnsignedInt() const;
			std::uint64_t GetUnsignedInt64() const;

			void SetInt(int value);
			void SetUnsignedInt(unsigned int value);
			void SetHexInt(unsigned int value);
			void SetHexInt(std::uint64_t value);
			void SetHexInt(const char* value);
			void SetWasHexa(bool value) { m_WasIntHexa = value; }

			void Clear() { *this = Variant(); }

		private:
			union {
				int m_IntValue;
				std::uint64_t m_UnsignedInt64Value{ 0 };
			};
			VariantType m_Type{ VariantType::VariantType_EmptyType };
			bool m_IsSigned;
			bool m_WasIntHexa;
	};

	std::ostream& operator<<(std::ostream& os, const Variant& variant);

}
