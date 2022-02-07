#include "CppIDLVariant.h"

namespace cppidl {

	int Variant::GetInt() const {
		assert(IsInt());
		return m_IntValue;
	}

	unsigned int Variant::GetUnsignedInt() const {
		assert(IsInt() || m_Type == VariantType::VariantType_UnsignedInt64Type);
		return m_IntValue;
	}

	std::uint64_t Variant::GetUnsignedInt64() const {
		assert(m_Type == VariantType::VariantType_UnsignedInt64Type);
		return m_UnsignedInt64Value;
	}

	void Variant::SetInt(int value) {
		m_IntValue = value;
		m_Type = VariantType::VariantType_IntType;
		m_WasIntHexa = false;
		m_IsSigned = true;
	}

	void Variant::SetUnsignedInt(unsigned int value) {
		m_IntValue = value;
		m_Type = VariantType::VariantType_IntType;
		m_WasIntHexa = false;
		m_IsSigned = false;
	}

	void Variant::SetHexInt(unsigned int value) {
		m_IntValue = value;
		m_Type = VariantType::VariantType_IntType;
		m_WasIntHexa = true;
	}

	void Variant::SetHexInt(std::uint64_t value) {
		m_UnsignedInt64Value = value;
		m_Type = VariantType::VariantType_UnsignedInt64Type;
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

	std::ostream& operator<<(std::ostream& os, const Variant& variant) {

		if (variant.GetWasHexa()) {
			os << "0x" << std::hex;
		}

		switch (variant.GetType())
		{
		case VariantType::VariantType_IntType:
			if (variant.GetIsSigned())
				os << variant.GetInt();
			else if (variant.GetUnsignedInt() > 0x7FFFFFFF)
				os << variant.GetUnsignedInt() << 'U';
			else
				os << variant.GetUnsignedInt();
			break;
		case VariantType::VariantType_UnsignedInt64Type:
			os << variant.GetUnsignedInt64();
			break;
		default:
			os << "Unknown type";
			break;
		}

		os << std::dec;

		return os;
	}

}
