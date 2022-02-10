enum SymbolConstants
{
   SYM_EOF                       =  0, // (EOF)
   SYM_ERROR                     =  1, // (Error)
   SYM_COMMENT                   =  2, // Comment
   SYM_NEWLINE                   =  3, // NewLine
   SYM_WHITESPACE                =  4, // Whitespace
   SYM_TIMESDIV                  =  5, // '*/'
   SYM_DIVTIMES                  =  6, // '/*'
   SYM_DIVDIV                    =  7, // '//'
   SYM_MINUS                     =  8, // '-'
   SYM_COMMA                     =  9, // ','
   SYM_COLON                     = 10, // ':'
   SYM_COLONCOLON                = 11, // '::'
   SYM_SEMI                      = 12, // ';'
   SYM_LBRACE                    = 13, // '{'
   SYM_PIPE                      = 14, // '|'
   SYM_RBRACE                    = 15, // '}'
   SYM_PLUS                      = 16, // '+'
   SYM_EQ                        = 17, // '='
   SYM_CLASS                     = 18, // class
   SYM_CODESTRING                = 19, // CodeString
   SYM_DECNUMBER                 = 20, // DecNumber
   SYM_ENUM                      = 21, // enum
   SYM_HEXNUMBER                 = 22, // HexNumber
   SYM_IDENTIFIER                = 23, // Identifier
   SYM_STRING                    = 24, // String
   SYM_ENUM2                     = 25, // <Enum>
   SYM_ENUMCLASSDECLARATION      = 26, // <EnumClassDeclaration>
   SYM_ENUMCOMBINAISON           = 27, // <EnumCombinaison>
   SYM_ENUMDECLARATION           = 28, // <EnumDeclaration>
   SYM_ENUMDECLARATIONIDENTIFIER = 29, // <EnumDeclarationIdentifier>
   SYM_ENUMTYPESPECIFICATION     = 30, // <EnumTypeSpecification>
   SYM_ENUMVALUE                 = 31, // <EnumValue>
   SYM_ENUMVALUECODE             = 32, // <EnumValueCode>
   SYM_ENUMVALUES                = 33, // <EnumValues>
   SYM_FILE                      = 34, // <File>
   SYM_LINECAPTURE               = 35, // <LineCapture>
   SYM_OPTIONALSEMICOLON         = 36, // <OptionalSemiColon>
   SYM_SCOPEDIDENTIFIER          = 37, // <ScopedIdentifier>
   SYM_SIGNEDNUMBER              = 38, // <SignedNumber>
   SYM_STATEMENT                 = 39, // <Statement>
   SYM_TYPEDECLARATION           = 40, // <TypeDeclaration>
   SYM_TYPEFORWARDDECLARATION    = 41, // <TypeForwardDeclaration>
   SYM_TYPEIDENTIFIER            = 42, // <TypeIdentifier>
   SYM_UNSIGNEDNUMBER            = 43  // <UnsignedNumber>
};

enum ProductionConstants
{
   PROD_LINECAPTURE                                   =  0, // <LineCapture> ::= 
   PROD_OPTIONALSEMICOLON_SEMI                        =  1, // <OptionalSemiColon> ::= ';'
   PROD_OPTIONALSEMICOLON                             =  2, // <OptionalSemiColon> ::= 
   PROD_TYPEIDENTIFIER                                =  3, // <TypeIdentifier> ::= <ScopedIdentifier>
   PROD_SCOPEDIDENTIFIER_IDENTIFIER                   =  4, // <ScopedIdentifier> ::= Identifier
   PROD_SCOPEDIDENTIFIER_IDENTIFIER_COLONCOLON        =  5, // <ScopedIdentifier> ::= Identifier '::' <ScopedIdentifier>
   PROD_FILE                                          =  6, // <File> ::= <File> <Statement>
   PROD_FILE2                                         =  7, // <File> ::= 
   PROD_STATEMENT                                     =  8, // <Statement> ::= <TypeDeclaration>
   PROD_STATEMENT2                                    =  9, // <Statement> ::= <TypeForwardDeclaration>
   PROD_TYPEDECLARATION                               = 10, // <TypeDeclaration> ::= <EnumDeclaration>
   PROD_TYPEDECLARATION2                              = 11, // <TypeDeclaration> ::= <EnumClassDeclaration>
   PROD_TYPEFORWARDDECLARATION_ENUM                   = 12, // <TypeForwardDeclaration> ::= enum <LineCapture> <ScopedIdentifier> <OptionalSemiColon>
   PROD_TYPEFORWARDDECLARATION_ENUM_CLASS             = 13, // <TypeForwardDeclaration> ::= enum class <LineCapture> <ScopedIdentifier> <OptionalSemiColon>
   PROD_ENUMDECLARATION_ENUM_LBRACE_RBRACE            = 14, // <EnumDeclaration> ::= enum <EnumDeclarationIdentifier> <EnumTypeSpecification> '{' <EnumValues> '}' <OptionalSemiColon>
   PROD_ENUMCLASSDECLARATION_ENUM_CLASS_LBRACE_RBRACE = 15, // <EnumClassDeclaration> ::= enum class <EnumDeclarationIdentifier> <EnumTypeSpecification> '{' <EnumValues> '}' <OptionalSemiColon>
   PROD_ENUMDECLARATIONIDENTIFIER_IDENTIFIER          = 16, // <EnumDeclarationIdentifier> ::= <LineCapture> Identifier
   PROD_ENUMTYPESPECIFICATION_COLON                   = 17, // <EnumTypeSpecification> ::= ':' <TypeIdentifier>
   PROD_ENUMTYPESPECIFICATION                         = 18, // <EnumTypeSpecification> ::= 
   PROD_ENUMVALUES_COMMA                              = 19, // <EnumValues> ::= <EnumValue> ',' <EnumValues>
   PROD_ENUMVALUES                                    = 20, // <EnumValues> ::= <EnumValue>
   PROD_ENUMVALUE_IDENTIFIER                          = 21, // <EnumValue> ::= <LineCapture> Identifier
   PROD_ENUMVALUE_IDENTIFIER_EQ                       = 22, // <EnumValue> ::= <LineCapture> Identifier '=' <SignedNumber>
   PROD_ENUMVALUE_IDENTIFIER_EQ2                      = 23, // <EnumValue> ::= <LineCapture> Identifier '=' <EnumCombinaison>
   PROD_ENUMVALUE_IDENTIFIER_EQ3                      = 24, // <EnumValue> ::= <LineCapture> Identifier '=' <EnumValueCode>
   PROD_ENUMCOMBINAISON_PIPE                          = 25, // <EnumCombinaison> ::= <EnumCombinaison> '|' <Enum>
   PROD_ENUMCOMBINAISON_PLUS                          = 26, // <EnumCombinaison> ::= <EnumCombinaison> '+' <SignedNumber>
   PROD_ENUMCOMBINAISON                               = 27, // <EnumCombinaison> ::= <Enum>
   PROD_ENUM                                          = 28, // <Enum> ::= <ScopedIdentifier>
   PROD_ENUMVALUECODE_STRING                          = 29, // <EnumValueCode> ::= String
   PROD_ENUMVALUECODE_CODESTRING                      = 30, // <EnumValueCode> ::= CodeString
   PROD_SIGNEDNUMBER_MINUS                            = 31, // <SignedNumber> ::= '-' <UnsignedNumber>
   PROD_SIGNEDNUMBER                                  = 32, // <SignedNumber> ::= <UnsignedNumber>
   PROD_UNSIGNEDNUMBER_DECNUMBER                      = 33, // <UnsignedNumber> ::= DecNumber
   PROD_UNSIGNEDNUMBER_HEXNUMBER                      = 34  // <UnsignedNumber> ::= HexNumber
};
