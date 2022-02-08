#pragma once

#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <iostream>

namespace cppidl {

	enum class VariantType {
		VariantType_Empty,
		VariantType_Int,
		VariantType_UnsignedInt64,
		VariantType_Float,
		VariantType_Double,
		VariantType_Bool,
		VariantType_String,
		VariantType_Enum,
		VariantType_Count
	};

	class Variant {

		public:
			Variant() = default;

			bool IsEnum() const { return m_Type == VariantType::VariantType_Enum; }
			bool IsEmpty() const { return m_Type == VariantType::VariantType_Empty; }
			bool IsInt() const { return m_Type == VariantType::VariantType_Int || IsEnum(); }
			bool IsBool() const { return m_Type == VariantType::VariantType_Bool; }
			bool IsFloat() const { return m_Type == VariantType::VariantType_Float; }
			bool IsDouble() const { return m_Type == VariantType::VariantType_Double; }
			bool IsString() const { return m_Type == VariantType::VariantType_String; }

			VariantType GetType() const { return m_Type; }
			bool GetIsSigned() const { return m_IsSigned; }
			bool GetWasHexa() const { return m_WasIntHexa; }

			bool GetBool() const;
			int GetInt() const;
			unsigned int GetUnsignedInt() const;
			std::uint64_t GetUnsignedInt64() const;
			float GetFloat() const;
			double GetDouble() const;
			const std::string& GetString() const;

			int GetEnumValue() const;
			std::string_view GetEnumString() const;
			std::pair<int, std::string> GetEnum() const;

			void SetInt(int value);
			void SetUnsignedInt(unsigned int value);
			void SetHexInt(unsigned int value);
			void SetHexInt(std::uint64_t value);
			void SetHexInt(const char* value);
			void SetWasHexa(bool value) { m_WasIntHexa = value; }
			void SetBool(bool value);
			void SetBool(const char* value);
			void SetFloat(float value);
			void SetDouble(double value);
			void SetString(std::string_view value);
			void SetEnum(std::string_view valueName, int value);

			void Clear() { *this = Variant(); }

		private:
			std::string m_StringValue;
			union {
				bool m_BoolValue;
				int m_IntValue;
				double m_DoubleValue;
				std::uint64_t m_UnsignedInt64Value{ 0 };
			};
			VariantType m_Type{ VariantType::VariantType_Empty };
			bool m_IsSigned;
			bool m_WasIntHexa;
	};

	std::ostream& operator<<(std::ostream& os, const Variant& variant);

}
