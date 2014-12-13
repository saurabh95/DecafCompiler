

%{
#include "ast.hh"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "parser.tab.hh"    

extern "C" int yylex();
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
type int|boolean



%%

"class" {  return CLASS;}
"{" {  return LC;}
"}" { return RC;}
"(" { return LP;}
")" {return RP;}
"[" {return LS;}
"]" {return RS;}
";" { return SEMICOLON;}
"!" { 
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return NOT;
}

"return" { return RETURN;}
"+" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return ADD;
}
"-" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return MINUS;
}
"*" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return MULTIPLY;
}
"/" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return DIVIDE;
}
"%" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return REMAINDER;
}
"=" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return EQUAL;
}
"+=" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return PLUSEQUAL;}
"-=" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return MINUSEQUAL;}

"continue" {return CONTINUE;}
"void" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return TYPE;
}
{type} {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return TYPE;
}

"while" {return WHILE;}

"for" {return FOR;}

"if" {return IF;}
"else" {return ELSE;}
"break" return BREAK;
"callout" return CALLOUT;
">"|"<"|">="|"<="  {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return ROP;
}
"&&" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return ANDAND;}
"||" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return OROR;}
"=="|"!=" {
    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
    strncpy(yylval.string, yytext, yyleng + 1);
    return EOP;
}

true|false { 
yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
strncpy(yylval.string, yytext, yyleng + 1);
return BOOLIT;}

{delim} {;}

"," return COMMA;

{comments} {;}

{id} {
 yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                  strncpy(yylval.string, yytext, yyleng + 1);
return ID;
}

{number} {
 yylval.integer = atoi(yytext);
return NUMBER;}


{hexit} { return HEXIT; }

"'"{character}"'" {
 yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                  strncpy(yylval.string, yytext+1, yyleng -2);
                  yylval.string[yyleng-2]='\0';
return CHARACTER;
}

\"{character}*\" {
yylval.string=(char*)malloc((yyleng+1)*(sizeof(char)));
                        strncpy(yylval.string,yytext+1,yyleng-2);
                        yylval.string[yyleng-2]='\0';
return STRINGIT;
}




%%

