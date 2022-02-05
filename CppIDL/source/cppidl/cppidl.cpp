enum SymbolConstants
{
   SYM_EOF                          =  0, // (EOF)
   SYM_ERROR                        =  1, // (Error)
   SYM_COMMENT                      =  2, // Comment
   SYM_NEWLINE                      =  3, // NewLine
   SYM_WHITESPACE                   =  4, // Whitespace
   SYM_TIMESDIV                     =  5, // '*/'
   SYM_DIVTIMES                     =  6, // '/*'
   SYM_DIVDIV                       =  7, // '//'
   SYM_MINUS                        =  8, // '-'
   SYM_LPAREN                       =  9, // '('
   SYM_RPAREN                       = 10, // ')'
   SYM_TIMES                        = 11, // '*'
   SYM_COMMA                        = 12, // ','
   SYM_COLON                        = 13, // ':'
   SYM_COLONCOLON                   = 14, // '::'
   SYM_SEMI                         = 15, // ';'
   SYM_LBRACKET                     = 16, // '['
   SYM_RBRACKET                     = 17, // ']'
   SYM_LBRACE                       = 18, // '{'
   SYM_PIPE                         = 19, // '|'
   SYM_RBRACE                       = 20, // '}'
   SYM_PLUS                         = 21, // '+'
   SYM_LT                           = 22, // '<'
   SYM_EQ                           = 23, // '='
   SYM_GT                           = 24, // '>'
   SYM_BOOLEAN                      = 25, // Boolean
   SYM_CLASS                        = 26, // class
   SYM_CODESTRING                   = 27, // CodeString
   SYM_CONST                        = 28, // const
   SYM_DECNUMBER                    = 29, // DecNumber
   SYM_DOUBLE                       = 30, // Double
   SYM_ENUM                         = 31, // enum
   SYM_FLOAT                        = 32, // Float
   SYM_HEXNUMBER                    = 33, // HexNumber
   SYM_IDENTIFIER                   = 34, // Identifier
   SYM_IN                           = 35, // in
   SYM_INOUT                        = 36, // inout
   SYM_OUT                          = 37, // out
   SYM_RETVAL                       = 38, // retval
   SYM_STATIC                       = 39, // static
   SYM_STRING                       = 40, // String
   SYM_STRUCT                       = 41, // struct
   SYM_VOID                         = 42, // void
   SYM_ATTRIBUTE                    = 43, // <Attribute>
   SYM_ATTRIBUTEGROUP               = 44, // <AttributeGroup>
   SYM_ATTRIBUTELIST                = 45, // <AttributeList>
   SYM_ATTRIBUTEPARAM               = 46, // <AttributeParam>
   SYM_ATTRIBUTEPARAMLIST           = 47, // <AttributeParamList>
   SYM_BASICTYPE                    = 48, // <BasicType>
   SYM_CLASSDECLARATION             = 49, // <ClassDeclaration>
   SYM_CLASSDECLARATIONIDENTIFIER   = 50, // <ClassDeclarationIdentifier>
   SYM_COMPLETEIDENTIFIER           = 51, // <CompleteIdentifier>
   SYM_ENUM2                        = 52, // <Enum>
   SYM_ENUMCOMBINAISON              = 53, // <EnumCombinaison>
   SYM_ENUMDECLARATION              = 54, // <EnumDeclaration>
   SYM_ENUMDECLARATIONIDENTIFIER    = 55, // <EnumDeclarationIdentifier>
   SYM_ENUMTYPESPECIFICATION        = 56, // <EnumTypeSpecification>
   SYM_ENUMVALUE                    = 57, // <EnumValue>
   SYM_ENUMVALUECODE                = 58, // <EnumValueCode>
   SYM_ENUMVALUES                   = 59, // <EnumValues>
   SYM_EXTENDCLAUSE                 = 60, // <ExtendClause>
   SYM_FILE                         = 61, // <File>
   SYM_LINECAPTURE                  = 62, // <LineCapture>
   SYM_METHODDECLARATION            = 63, // <MethodDeclaration>
   SYM_METHODIDENTIFIER             = 64, // <MethodIdentifier>
   SYM_METHODOPTIONALCONST          = 65, // <MethodOptionalConst>
   SYM_METHODPARAM                  = 66, // <MethodParam>
   SYM_METHODPARAMLIST              = 67, // <MethodParamList>
   SYM_METHODPARAMMODIFIER          = 68, // <MethodParamModifier>
   SYM_METHODVAR                    = 69, // <MethodVar>
   SYM_OPTIONALDEFAULTVALUE         = 70, // <OptionalDefaultValue>
   SYM_OPTIONALSEMICOLON            = 71, // <OptionalSemiColon>
   SYM_SCOPEDIDENTIFIER             = 72, // <ScopedIdentifier>
   SYM_SIGNEDDOUBLE                 = 73, // <SignedDouble>
   SYM_SIGNEDFLOAT                  = 74, // <SignedFloat>
   SYM_SIGNEDNUMBER                 = 75, // <SignedNumber>
   SYM_STATEMENT                    = 76, // <Statement>
   SYM_STATICARRAYSIZE              = 77, // <StaticArraySize>
   SYM_STATICSCOPE                  = 78, // <StaticScope>
   SYM_STRUCTDECLARATION            = 79, // <StructDeclaration>
   SYM_STRUCTDECLARATIONIDENTIFIER  = 80, // <StructDeclarationIdentifier>
   SYM_TYPE                         = 81, // <Type>
   SYM_TYPEDECLARATION              = 82, // <TypeDeclaration>
   SYM_TYPEDEFINITION               = 83, // <TypeDefinition>
   SYM_TYPEDEFINITIONELEMENT        = 84, // <TypeDefinitionElement>
   SYM_TYPEFORWARDDECLARATION       = 85, // <TypeForwardDeclaration>
   SYM_TYPEIDENTIFIER               = 86, // <TypeIdentifier>
   SYM_TYPEMODIFIER                 = 87, // <TypeModifier>
   SYM_UNSIGNEDDOUBLE               = 88, // <UnsignedDouble>
   SYM_UNSIGNEDFLOAT                = 89, // <UnsignedFloat>
   SYM_UNSIGNEDNUMBER               = 90, // <UnsignedNumber>
   SYM_VALUE                        = 91, // <Value>
   SYM_VALUELIST                    = 92, // <ValueList>
   SYM_VALUELISTBEGIN               = 93, // <ValueListBegin>
   SYM_VAR                          = 94, // <Var>
   SYM_VARATTRIBUTEGROUPBEGIN       = 95, // <VarAttributeGroupBegin>
   SYM_VARATTRIBUTEGROUPDECLARATION = 96, // <VarAttributeGroupDeclaration>
   SYM_VARDECLARATION               = 97  // <VarDeclaration>
};

enum ProductionConstants
{
   PROD_LINECAPTURE                                =  0, // <LineCapture> ::= 
   PROD_METHODIDENTIFIER_IDENTIFIER                =  1, // <MethodIdentifier> ::= Identifier
   PROD_VARATTRIBUTEGROUPBEGIN                     =  2, // <VarAttributeGroupBegin> ::= 
   PROD_ENUMDECLARATIONIDENTIFIER_IDENTIFIER       =  3, // <EnumDeclarationIdentifier> ::= <LineCapture> Identifier
   PROD_CLASSDECLARATIONIDENTIFIER_IDENTIFIER      =  4, // <ClassDeclarationIdentifier> ::= <LineCapture> Identifier
   PROD_STRUCTDECLARATIONIDENTIFIER_IDENTIFIER     =  5, // <StructDeclarationIdentifier> ::= <LineCapture> Identifier
   PROD_FILE                                       =  6, // <File> ::= <File> <Statement>
   PROD_FILE2                                      =  7, // <File> ::= 
   PROD_STATEMENT                                  =  8, // <Statement> ::= <TypeDeclaration>
   PROD_STATEMENT2                                 =  9, // <Statement> ::= <TypeForwardDeclaration>
   PROD_OPTIONALSEMICOLON_SEMI                     = 10, // <OptionalSemiColon> ::= ';'
   PROD_OPTIONALSEMICOLON                          = 11, // <OptionalSemiColon> ::= 
   PROD_COMPLETEIDENTIFIER                         = 12, // <CompleteIdentifier> ::= <TypeIdentifier>
   PROD_COMPLETEIDENTIFIER_IDENTIFIER_LT_GT        = 13, // <CompleteIdentifier> ::= Identifier '<' <TypeIdentifier> '>'
   PROD_TYPEIDENTIFIER                             = 14, // <TypeIdentifier> ::= <ScopedIdentifier>
   PROD_SCOPEDIDENTIFIER_IDENTIFIER                = 15, // <ScopedIdentifier> ::= Identifier
   PROD_SCOPEDIDENTIFIER_IDENTIFIER_COLONCOLON     = 16, // <ScopedIdentifier> ::= Identifier '::' <ScopedIdentifier>
   PROD_TYPEFORWARDDECLARATION_CLASS               = 17, // <TypeForwardDeclaration> ::= <AttributeGroup> class <LineCapture> <ScopedIdentifier> <OptionalSemiColon>
   PROD_TYPEFORWARDDECLARATION_STRUCT              = 18, // <TypeForwardDeclaration> ::= <AttributeGroup> struct <LineCapture> <ScopedIdentifier> <OptionalSemiColon>
   PROD_TYPEFORWARDDECLARATION_ENUM                = 19, // <TypeForwardDeclaration> ::= <AttributeGroup> enum <LineCapture> <ScopedIdentifier> <OptionalSemiColon>
   PROD_ENUMTYPESPECIFICATION_COLON                = 20, // <EnumTypeSpecification> ::= ':' <TypeIdentifier>
   PROD_ENUMTYPESPECIFICATION                      = 21, // <EnumTypeSpecification> ::= 
   PROD_ENUMDECLARATION_ENUM_LBRACE_RBRACE         = 22, // <EnumDeclaration> ::= <AttributeGroup> enum <EnumDeclarationIdentifier> <EnumTypeSpecification> '{' <EnumValues> '}' <OptionalSemiColon>
   PROD_CLASSDECLARATION_CLASS_LBRACE_RBRACE       = 23, // <ClassDeclaration> ::= <AttributeGroup> class <ClassDeclarationIdentifier> <ExtendClause> '{' <TypeDefinition> '}' <OptionalSemiColon>
   PROD_STRUCTDECLARATION_STRUCT_LBRACE_RBRACE     = 24, // <StructDeclaration> ::= <AttributeGroup> struct <StructDeclarationIdentifier> '{' <TypeDefinition> '}' <OptionalSemiColon>
   PROD_TYPEDECLARATION                            = 25, // <TypeDeclaration> ::= <EnumDeclaration>
   PROD_TYPEDECLARATION2                           = 26, // <TypeDeclaration> ::= <ClassDeclaration>
   PROD_TYPEDECLARATION3                           = 27, // <TypeDeclaration> ::= <StructDeclaration>
   PROD_ATTRIBUTEGROUP_LBRACKET_RBRACKET           = 28, // <AttributeGroup> ::= '[' <AttributeList> ']' <AttributeGroup>
   PROD_ATTRIBUTEGROUP                             = 29, // <AttributeGroup> ::= 
   PROD_ATTRIBUTELIST_COMMA                        = 30, // <AttributeList> ::= <Attribute> ',' <AttributeList>
   PROD_ATTRIBUTELIST                              = 31, // <AttributeList> ::= <Attribute>
   PROD_ATTRIBUTE_IDENTIFIER                       = 32, // <Attribute> ::= Identifier
   PROD_ATTRIBUTE_IDENTIFIER_LPAREN_RPAREN         = 33, // <Attribute> ::= Identifier '(' <AttributeParamList> ')'
   PROD_ATTRIBUTEPARAMLIST_COMMA                   = 34, // <AttributeParamList> ::= <AttributeParam> ',' <AttributeParamList>
   PROD_ATTRIBUTEPARAMLIST                         = 35, // <AttributeParamList> ::= <AttributeParam>
   PROD_ATTRIBUTEPARAM                             = 36, // <AttributeParam> ::= <Value>
   PROD_EXTENDCLAUSE_COLON                         = 37, // <ExtendClause> ::= ':' <ScopedIdentifier>
   PROD_EXTENDCLAUSE                               = 38, // <ExtendClause> ::= 
   PROD_ENUMVALUES_COMMA                           = 39, // <EnumValues> ::= <EnumValue> ',' <EnumValues>
   PROD_ENUMVALUES                                 = 40, // <EnumValues> ::= <EnumValue>
   PROD_ENUMCOMBINAISON_PIPE                       = 41, // <EnumCombinaison> ::= <EnumCombinaison> '|' <Enum>
   PROD_ENUMCOMBINAISON_PLUS                       = 42, // <EnumCombinaison> ::= <EnumCombinaison> '+' <SignedNumber>
   PROD_ENUMCOMBINAISON                            = 43, // <EnumCombinaison> ::= <Enum>
   PROD_ENUMVALUECODE_STRING                       = 44, // <EnumValueCode> ::= String
   PROD_ENUMVALUECODE_CODESTRING                   = 45, // <EnumValueCode> ::= CodeString
   PROD_ENUMVALUE_IDENTIFIER                       = 46, // <EnumValue> ::= <AttributeGroup> <LineCapture> Identifier
   PROD_ENUMVALUE_IDENTIFIER_EQ                    = 47, // <EnumValue> ::= <AttributeGroup> <LineCapture> Identifier '=' <SignedNumber>
   PROD_ENUMVALUE_IDENTIFIER_EQ2                   = 48, // <EnumValue> ::= <AttributeGroup> <LineCapture> Identifier '=' <EnumCombinaison>
   PROD_ENUMVALUE_IDENTIFIER_EQ3                   = 49, // <EnumValue> ::= <AttributeGroup> <LineCapture> Identifier '=' <EnumValueCode>
   PROD_TYPEDEFINITION                             = 50, // <TypeDefinition> ::= <TypeDefinitionElement> <TypeDefinition>
   PROD_TYPEDEFINITION2                            = 51, // <TypeDefinition> ::= 
   PROD_TYPEDEFINITIONELEMENT                      = 52, // <TypeDefinitionElement> ::= <MethodDeclaration>
   PROD_TYPEDEFINITIONELEMENT2                     = 53, // <TypeDefinitionElement> ::= <VarAttributeGroupDeclaration>
   PROD_TYPEDEFINITIONELEMENT3                     = 54, // <TypeDefinitionElement> ::= <EnumDeclaration>
   PROD_TYPEDEFINITIONELEMENT4                     = 55, // <TypeDefinitionElement> ::= <VarDeclaration>
   PROD_STATICSCOPE_STATIC                         = 56, // <StaticScope> ::= static
   PROD_STATICSCOPE                                = 57, // <StaticScope> ::= 
   PROD_VARDECLARATION                             = 58, // <VarDeclaration> ::= <AttributeGroup> <StaticScope> <Type> <LineCapture> <Var> <OptionalDefaultValue> <OptionalSemiColon>
   PROD_VARATTRIBUTEGROUPDECLARATION_LBRACE_RBRACE = 59, // <VarAttributeGroupDeclaration> ::= <AttributeGroup> '{' <VarAttributeGroupBegin> <TypeDefinition> '}'
   PROD_METHODDECLARATION_VOID_LPAREN_RPAREN       = 60, // <MethodDeclaration> ::= <AttributeGroup> <StaticScope> void <LineCapture> <MethodIdentifier> '(' <MethodParamList> ')' <MethodOptionalConst> <OptionalSemiColon>
   PROD_METHODDECLARATION_LPAREN_RPAREN            = 61, // <MethodDeclaration> ::= <AttributeGroup> <StaticScope> <MethodIdentifier> <LineCapture> '(' <MethodParamList> ')' <MethodOptionalConst> <OptionalSemiColon>
   PROD_METHODOPTIONALCONST_CONST                  = 62, // <MethodOptionalConst> ::= const
   PROD_METHODOPTIONALCONST                        = 63, // <MethodOptionalConst> ::= 
   PROD_VAR_IDENTIFIER_COLON                       = 64, // <Var> ::= Identifier ':' <UnsignedNumber>
   PROD_VAR_IDENTIFIER                             = 65, // <Var> ::= Identifier
   PROD_VALUELISTBEGIN                             = 66, // <ValueListBegin> ::= 
   PROD_VALUELIST_COMMA                            = 67, // <ValueList> ::= <Value> <ValueListBegin> ',' <ValueList>
   PROD_VALUELIST                                  = 68, // <ValueList> ::= <Value>
   PROD_OPTIONALDEFAULTVALUE_EQ                    = 69, // <OptionalDefaultValue> ::= '=' <ValueList>
   PROD_OPTIONALDEFAULTVALUE                       = 70, // <OptionalDefaultValue> ::= 
   PROD_TYPE                                       = 71, // <Type> ::= <BasicType> <TypeModifier>
   PROD_BASICTYPE                                  = 72, // <BasicType> ::= <CompleteIdentifier>
   PROD_STATICARRAYSIZE                            = 73, // <StaticArraySize> ::= <UnsignedNumber>
   PROD_STATICARRAYSIZE2                           = 74, // <StaticArraySize> ::= <Enum>
   PROD_STATICARRAYSIZE_STRING                     = 75, // <StaticArraySize> ::= String
   PROD_STATICARRAYSIZE_CODESTRING                 = 76, // <StaticArraySize> ::= CodeString
   PROD_TYPEMODIFIER_TIMES                         = 77, // <TypeModifier> ::= '*'
   PROD_TYPEMODIFIER_TIMES_LBRACKET_RBRACKET       = 78, // <TypeModifier> ::= '*' '[' ']'
   PROD_TYPEMODIFIER_TIMES_LBRACKET_RBRACKET2      = 79, // <TypeModifier> ::= '*' '[' <StaticArraySize> ']'
   PROD_TYPEMODIFIER_LBRACKET_RBRACKET             = 80, // <TypeModifier> ::= '[' ']'
   PROD_TYPEMODIFIER_LBRACKET_RBRACKET2            = 81, // <TypeModifier> ::= '[' <StaticArraySize> ']'
   PROD_TYPEMODIFIER                               = 82, // <TypeModifier> ::= 
   PROD_METHODPARAMLIST_COMMA                      = 83, // <MethodParamList> ::= <MethodParam> ',' <MethodParamList>
   PROD_METHODPARAMLIST                            = 84, // <MethodParamList> ::= <MethodParam>
   PROD_METHODPARAMLIST2                           = 85, // <MethodParamList> ::= 
   PROD_METHODPARAM                                = 86, // <MethodParam> ::= <AttributeGroup> <MethodParamModifier> <Type> <MethodVar>
   PROD_METHODVAR_IDENTIFIER                       = 87, // <MethodVar> ::= Identifier
   PROD_METHODPARAMMODIFIER_OUT                    = 88, // <MethodParamModifier> ::= out
   PROD_METHODPARAMMODIFIER_IN                     = 89, // <MethodParamModifier> ::= in
   PROD_METHODPARAMMODIFIER_INOUT                  = 90, // <MethodParamModifier> ::= inout
   PROD_METHODPARAMMODIFIER_RETVAL                 = 91, // <MethodParamModifier> ::= retval
   PROD_METHODPARAMMODIFIER                        = 92, // <MethodParamModifier> ::= 
   PROD_UNSIGNEDNUMBER_DECNUMBER                   = 93, // <UnsignedNumber> ::= DecNumber
   PROD_UNSIGNEDNUMBER_HEXNUMBER                   = 94, // <UnsignedNumber> ::= HexNumber
   PROD_SIGNEDNUMBER_MINUS                         = 95, // <SignedNumber> ::= '-' <UnsignedNumber>
   PROD_SIGNEDNUMBER                               = 96, // <SignedNumber> ::= <UnsignedNumber>
   PROD_UNSIGNEDFLOAT_FLOAT                        = 97, // <UnsignedFloat> ::= Float
   PROD_SIGNEDFLOAT_MINUS                          = 98, // <SignedFloat> ::= '-' <UnsignedFloat>
   PROD_SIGNEDFLOAT                                = 99, // <SignedFloat> ::= <UnsignedFloat>
   PROD_UNSIGNEDDOUBLE_DOUBLE                      = 100, // <UnsignedDouble> ::= Double
   PROD_SIGNEDDOUBLE_MINUS                         = 101, // <SignedDouble> ::= '-' <UnsignedDouble>
   PROD_SIGNEDDOUBLE                               = 102, // <SignedDouble> ::= <UnsignedDouble>
   PROD_ENUM                                       = 103, // <Enum> ::= <ScopedIdentifier>
   PROD_VALUE                                      = 104, // <Value> ::= <SignedNumber>
   PROD_VALUE2                                     = 105, // <Value> ::= <SignedFloat>
   PROD_VALUE3                                     = 106, // <Value> ::= <SignedDouble>
   PROD_VALUE_STRING                               = 107, // <Value> ::= String
   PROD_VALUE_CODESTRING                           = 108, // <Value> ::= CodeString
   PROD_VALUE_BOOLEAN                              = 109, // <Value> ::= Boolean
   PROD_VALUE4                                     = 110, // <Value> ::= <Enum>
   PROD_VALUE_VOID                                 = 111  // <Value> ::= void
};
