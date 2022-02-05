#pragma once

#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <iostream>

namespace cppidl {

	enum class VariantType {
		EmptyType,
		IntType,
		UnsignedInt64Type,
		Count
	};

	class Variant {

		public:
			Variant() = default;

			bool IsEmpty() const { return m_Type == VariantType::EmptyType; }
			bool IsInt() const { return m_Type == VariantType::IntType; }

			VariantType GetType() const { return m_Type; }
			bool GetIsSigned() const { return m_IsSigned; }
			bool GetWasHexa() const { return m_WasIntHexa; }

			int GetInt() const {
				assert(IsInt());
				return m_IntValue;
			}

			unsigned int GetUnsignedInt() const {
				assert(IsInt() || m_Type == VariantType::UnsignedInt64Type);
				return m_IntValue;
			}

			std::uint64_t GetUnsignedInt64() const {
				assert(m_Type == VariantType::UnsignedInt64Type);
				return m_UnsignedInt64Value;
			}

			void SetInt(int value) {
				m_IntValue = value;
				m_Type = VariantType::IntType;
				m_WasIntHexa = false;
				m_IsSigned = true;
			}

			void SetUnsignedInt(unsigned int value) {
				m_IntValue = value;
				m_Type = VariantType::IntType;
				m_WasIntHexa = false;
				m_IsSigned = false;
			}

			void SetHexInt(unsigned int value) {
				m_IntValue = value;
				m_Type = VariantType::IntType;
				m_WasIntHexa = true;
			}

			void SetHexInt(std::uint64_t value) {
				m_UnsignedInt64Value = value;
				m_Type = VariantType::UnsignedInt64Type;
				m_WasIntHexa = true;
			}

			void SetHexInt(const char* valueStr) {
				char* eptr = nullptr;

				std::uint64_t value = strtoll(valueStr, &eptr, 16);
				if (value < std::uint64_t(0x100000000))
					SetHexInt(unsigned(value));
				else
					SetHexInt(value);
			}

			void SetWasHexa(bool value) { m_WasIntHexa = value; }

			void Clear() { *this = Variant(); }

		private:
			union {
				int m_IntValue;
				std::uint64_t m_UnsignedInt64Value{ 0 };
			};
			VariantType m_Type{ VariantType::EmptyType };
			bool m_IsSigned;
			bool m_WasIntHexa;
	};

	std::ostream& operator<<(std::ostream& os, const Variant& variant);

}
