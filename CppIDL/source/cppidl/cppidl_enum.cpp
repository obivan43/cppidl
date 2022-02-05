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
   SYM_CODESTRING                = 18, // CodeString
   SYM_DECNUMBER                 = 19, // DecNumber
   SYM_ENUM                      = 20, // enum
   SYM_HEXNUMBER                 = 21, // HexNumber
   SYM_IDENTIFIER                = 22, // Identifier
   SYM_STRING                    = 23, // String
   SYM_ENUM2                     = 24, // <Enum>
   SYM_ENUMCOMBINAISON           = 25, // <EnumCombinaison>
   SYM_ENUMDECLARATION           = 26, // <EnumDeclaration>
   SYM_ENUMDECLARATIONIDENTIFIER = 27, // <EnumDeclarationIdentifier>
   SYM_ENUMTYPESPECIFICATION     = 28, // <EnumTypeSpecification>
   SYM_ENUMVALUE                 = 29, // <EnumValue>
   SYM_ENUMVALUECODE             = 30, // <EnumValueCode>
   SYM_ENUMVALUES                = 31, // <EnumValues>
   SYM_FILE                      = 32, // <File>
   SYM_LINECAPTURE               = 33, // <LineCapture>
   SYM_OPTIONALSEMICOLON         = 34, // <OptionalSemiColon>
   SYM_SCOPEDIDENTIFIER          = 35, // <ScopedIdentifier>
   SYM_SIGNEDNUMBER              = 36, // <SignedNumber>
   SYM_STATEMENT                 = 37, // <Statement>
   SYM_TYPEDECLARATION           = 38, // <TypeDeclaration>
   SYM_TYPEFORWARDDECLARATION    = 39, // <TypeForwardDeclaration>
   SYM_TYPEIDENTIFIER            = 40, // <TypeIdentifier>
   SYM_UNSIGNEDNUMBER            = 41  // <UnsignedNumber>
};

enum ProductionConstants
{
   PROD_LINECAPTURE                            =  0, // <LineCapture> ::= 
   PROD_OPTIONALSEMICOLON_SEMI                 =  1, // <OptionalSemiColon> ::= ';'
   PROD_OPTIONALSEMICOLON                      =  2, // <OptionalSemiColon> ::= 
   PROD_TYPEIDENTIFIER                         =  3, // <TypeIdentifier> ::= <ScopedIdentifier>
   PROD_SCOPEDIDENTIFIER_IDENTIFIER            =  4, // <ScopedIdentifier> ::= Identifier
   PROD_SCOPEDIDENTIFIER_IDENTIFIER_COLONCOLON =  5, // <ScopedIdentifier> ::= Identifier '::' <ScopedIdentifier>
   PROD_FILE                                   =  6, // <File> ::= <File> <Statement>
   PROD_FILE2                                  =  7, // <File> ::= 
   PROD_STATEMENT                              =  8, // <Statement> ::= <TypeDeclaration>
   PROD_STATEMENT2                             =  9, // <Statement> ::= <TypeForwardDeclaration>
   PROD_TYPEDECLARATION                        = 10, // <TypeDeclaration> ::= <EnumDeclaration>
   PROD_TYPEFORWARDDECLARATION_ENUM            = 11, // <TypeForwardDeclaration> ::= enum <LineCapture> <ScopedIdentifier> <OptionalSemiColon>
   PROD_ENUMDECLARATION_ENUM_LBRACE_RBRACE     = 12, // <EnumDeclaration> ::= enum <EnumDeclarationIdentifier> <EnumTypeSpecification> '{' <EnumValues> '}' <OptionalSemiColon>
   PROD_ENUMDECLARATIONIDENTIFIER_IDENTIFIER   = 13, // <EnumDeclarationIdentifier> ::= <LineCapture> Identifier
   PROD_ENUMTYPESPECIFICATION_COLON            = 14, // <EnumTypeSpecification> ::= ':' <TypeIdentifier>
   PROD_ENUMTYPESPECIFICATION                  = 15, // <EnumTypeSpecification> ::= 
   PROD_ENUMVALUES_COMMA                       = 16, // <EnumValues> ::= <EnumValue> ',' <EnumValues>
   PROD_ENUMVALUES                             = 17, // <EnumValues> ::= <EnumValue>
   PROD_ENUMVALUE_IDENTIFIER                   = 18, // <EnumValue> ::= <LineCapture> Identifier
   PROD_ENUMVALUE_IDENTIFIER_EQ                = 19, // <EnumValue> ::= <LineCapture> Identifier '=' <SignedNumber>
   PROD_ENUMVALUE_IDENTIFIER_EQ2               = 20, // <EnumValue> ::= <LineCapture> Identifier '=' <EnumCombinaison>
   PROD_ENUMVALUE_IDENTIFIER_EQ3               = 21, // <EnumValue> ::= <LineCapture> Identifier '=' <EnumValueCode>
   PROD_ENUMCOMBINAISON_PIPE                   = 22, // <EnumCombinaison> ::= <EnumCombinaison> '|' <Enum>
   PROD_ENUMCOMBINAISON_PLUS                   = 23, // <EnumCombinaison> ::= <EnumCombinaison> '+' <SignedNumber>
   PROD_ENUMCOMBINAISON                        = 24, // <EnumCombinaison> ::= <Enum>
   PROD_ENUM                                   = 25, // <Enum> ::= <ScopedIdentifier>
   PROD_ENUMVALUECODE_STRING                   = 26, // <EnumValueCode> ::= String
   PROD_ENUMVALUECODE_CODESTRING               = 27, // <EnumValueCode> ::= CodeString
   PROD_SIGNEDNUMBER_MINUS                     = 28, // <SignedNumber> ::= '-' <UnsignedNumber>
   PROD_SIGNEDNUMBER                           = 29, // <SignedNumber> ::= <UnsignedNumber>
   PROD_UNSIGNEDNUMBER_DECNUMBER               = 30, // <UnsignedNumber> ::= DecNumber
   PROD_UNSIGNEDNUMBER_HEXNUMBER               = 31  // <UnsignedNumber> ::= HexNumber
};
