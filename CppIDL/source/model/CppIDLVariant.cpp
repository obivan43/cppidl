#include "CppIDLVariant.h"

namespace cppidl {

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
