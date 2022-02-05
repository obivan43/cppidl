#include "cppidlparser.h"

int main(int argc, char* argv[]) {
	std::string inputFile = "data/test.cppidl";

	cppidl::CppIDLParser parser;
	parser.Parse(inputFile.c_str());

	system("pause");
	return 0;
}
