
%{
    #include<stdio.h>
    int yylex();
    void yyerror(const char * s ){printf("ERROR: %s\n",s);}
%}

%token CLASS PROGRAM LC RC LP RP LS RS VOID INT BOOL WHILE FOR IF ELSE BREAK CONTINUE ROP COP EOP BOOLIT HEX DIG STOP COMMA EQ NUMBER ID

%token  SEMICOLON NOT RETURN ADD MINUS MULTIPLY DIVIDE EQUAL CHARCTER STRINGIT CALLOUT CHARACTER HEXIT MINUSEQUAL PLUSEQUAL REMAINDER

%token ANDAND OROR TYPE

%start program
%glr-parser

%left NOT
%left MULTIPLY DIVIDE REMAINDER
%left ADD MINUS
%left ROP
%left EOP
%left ANDAND OROR


%%

ASOP: EQUAL|PLUSEQUAL|MINUSEQUAL

program: CLASS ID LC fieldmore RC


fieldmore: | field fieldmore | method fieldmore 


field: TYPE variables SEMICOLON


variables: variable
          | variables COMMA variable

variable: ID 
        | ID LS NUMBER RS

method: VOID ID LP method_arguments RP block 
       |TYPE ID LP method_arguments RP block 

method_arguments: | TYPE ID 
                | method_arguments COMMA TYPE ID

block: LC var_declmore statementmore RC

var_declmore: | var_decl var_declmore

statementmore: | statement statementmore

var_decl: TYPE mvariables SEMICOLON

mvariables: ID
          | mvariables COMMA ID

statement: location ASOP expr SEMICOLON
          | method_call SEMICOLON
          | IF LP expr  RP block
          | IF LP expr  RP block ELSE block
          | FOR ID EQUAL expr COMMA expr block
          | RETURN expr SEMICOLON
          | RETURN SEMICOLON
          | CONTINUE SEMICOLON
          | block


method_call: method_name LP  method_call_arguments  RP
            | CALLOUT  LP stringit  RP
            | CALLOUT LP stringit COMMA callout_argmore  RP

callout_argmore: callout_arg | callout_argmore COMMA callout_arg

method_name: ID

location: ID
        | ID LS expr  RS

expr: location
    | method_call
    | literal
    | MINUS expr
    | NOT expr
    | LP expr  RP
    | expr ADD expr
    | expr MINUS expr
    | expr MULTIPLY expr
    | expr DIVIDE expr
    | expr REMAINDER expr
    | expr ROP expr
    | expr EOP expr
    | expr ANDAND expr
    | expr OROR expr

method_call_arguments: | expr | method_call_arguments COMMA expr

callout_arg: expr
            | stringit

literal: int_literal
        | char_literal
        | BOOLIT



int_literal: NUMBER | HEXIT


char_literal: CHARACTER

stringit: STRINGIT


%%

int main()
{
    while(yyparse());
    return 0;
}
