#include "CppIDLVariant.h"

namespace cppidl {

	bool Variant::GetBool() const{
		assert(IsBool());
		return m_BoolValue;
	}

	int Variant::GetInt() const {
		assert(IsInt());
		return m_IntValue;
	}

	unsigned int Variant::GetUnsignedInt() const {
		assert(IsInt() || m_Type == VariantType::VariantType_UnsignedInt64 || m_Type == VariantType::VariantType_Enum);
		return m_IntValue;
	}

	std::uint64_t Variant::GetUnsignedInt64() const {
		assert(m_Type == VariantType::VariantType_UnsignedInt64);
		return m_UnsignedInt64Value;
	}

	float Variant::GetFloat() const {
		assert(IsFloat());
		return static_cast<float>(m_DoubleValue);
	}

	double Variant::GetDouble() const {
		assert(IsDouble());
		return m_DoubleValue;
	}

	int Variant::GetEnumValue() const {
		assert(IsEnum());
		return m_IntValue;
	}

	std::string_view Variant::GetEnumString() const {
		assert(IsEnum());
		return m_StringValue;
	}

	std::pair<int, std::string> Variant::GetEnum() const {
		assert(IsEnum());
		return {m_IntValue, m_StringValue};
	}

	const std::string& Variant::GetString() const {
		assert(IsString());
		return m_StringValue;
	}

	void Variant::SetInt(int value) {
		m_IntValue = value;
		m_Type = VariantType::VariantType_Int;
		m_WasIntHexa = false;
		m_IsSigned = true;
	}

	void Variant::SetUnsignedInt(unsigned int value) {
		m_IntValue = value;
		m_Type = VariantType::VariantType_Int;
		m_WasIntHexa = false;
		m_IsSigned = false;
	}

	void Variant::SetHexInt(unsigned int value) {
		m_IntValue = value;
		m_Type = VariantType::VariantType_Int;
		m_WasIntHexa = true;
	}

	void Variant::SetHexInt(std::uint64_t value) {
		m_UnsignedInt64Value = value;
		m_Type = VariantType::VariantType_UnsignedInt64;
		m_WasIntHexa = true;
	}

	void Variant::SetHexInt(const char* value) {
		char* eptr = nullptr;

		std::uint64_t convertedValue = strtoll(value, &eptr, 16);
		if (convertedValue < std::uint64_t(0x100000000))
			SetHexInt(unsigned(convertedValue));
		else
			SetHexInt(convertedValue);
	}

	void Variant::SetFloat(float value) {
		m_DoubleValue = value;
		m_Type = VariantType::VariantType_Float;
	}

	void Variant::SetDouble(double value) {
		m_DoubleValue = value;
		m_Type = VariantType::VariantType_Double;
	}

	void Variant::SetBool(bool value) {
		m_BoolValue = value;
		m_Type = VariantType::VariantType_Bool;
	}

	void Variant::SetBool(const char* value) { SetBool(std::string(value) == "true"); }

	void Variant::SetEnum(std::string_view valueName, int value) {
		m_StringValue = valueName;
		m_IntValue = value;
		m_Type = VariantType::VariantType_Enum;
	}

	void Variant::SetString(std::string_view value) {
		m_StringValue = value;
		m_Type = VariantType::VariantType_String;
	}

	std::ostream& operator<<(std::ostream& os, const Variant& variant) {

		if (variant.GetWasHexa()) {
			os << "0x" << std::hex;
		}

		switch (variant.GetType())
		{
		case VariantType::VariantType_Bool:
			os << (variant.GetBool() ? "true" : "false");
			break;
		case VariantType::VariantType_Double:
			os << variant.GetDouble();
			break;
		case VariantType::VariantType_Float:
			os << variant.GetFloat();
			break;
		case VariantType::VariantType_Int:
			if (variant.GetIsSigned())
				os << variant.GetInt();
			else if (variant.GetUnsignedInt() > 0x7FFFFFFF)
				os << variant.GetUnsignedInt() << 'U';
			else
				os << variant.GetUnsignedInt();
			break;
		case VariantType::VariantType_UnsignedInt64:
			os << variant.GetUnsignedInt64();
			break;
		case VariantType::VariantType_String:
			os << variant.GetString();
			break;
		case VariantType::VariantType_Enum: {
			std::pair<int, std::string> enumValue = variant.GetEnum();
			os << enumValue.first << " " << enumValue.second;
		}
			break;
		default:
			os << "Unknown type";
			break;
		}

		os << std::dec;

		return os;
	}

}
