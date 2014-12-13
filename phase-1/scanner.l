

%{
#include<stdio.h>
#include "parser.tab.h"    

extern int yylex();
%}

delim [ \t\n]
ws {delim}+
alpha [A-Za-z]
digit [0-9]
comments "//".*
id {alpha}({alpha}|{digit})*
number {digit}+(\.{digit}+)?(E[+-]?{digit}+)?
hexit 0x({digit}|[a-fA-F])+
character (\\n|\\t|\\'|\\\\|\\\"|[^\\"'])



%%

"class" {  return CLASS;}
"{" {  return LC;}
"}" { return RC;}
"(" { return LP;}
")" {return RP;}
"[" {return LS;}
"]" {return RS;}
";" { return SEMICOLON;}
"!" { return NOT;}

"return" { return RETURN;}
"+" {return ADD;}
"-" {return MINUS;}
"*" {return MULTIPLY;}
"/" {return DIVIDE;}
"%" return REMAINDER;
"=" {return EQUAL;}
"+=" {return PLUSEQUAL;}
"-=" {return MINUSEQUAL;}

"continue" {return CONTINUE;}
"void" {return VOID;}
"int"|"boolean" {return TYPE;}
"while" {return WHILE;}

"for" {return FOR;}

"if" {return IF;}
"else" {return ELSE;}
"break" return BREAK;
"callout" return CALLOUT;
">"|"<"|">="|"<="  {return ROP;}
"&&" {return ANDAND;}
"||" {return OROR;}
"=="|"!=" return EOP;
true|false return BOOLIT;

{delim} {;}
"," return COMMA;
{comments} {;}
{id} return ID;
{number} return NUMBER;
{hexit} return HEXIT;
{character} return CHARACTER;

\"{character}*\" return STRINGIT;




%%

