/* A Bison parser, made by GNU Bison 2.5.  */

/* Skeleton interface for Bison GLR parsers in C
   
      Copyright (C) 2002-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NOT = 258,
     REMAINDER = 259,
     DIVIDE = 260,
     MULTIPLY = 261,
     MINUS = 262,
     ADD = 263,
     ROP = 264,
     EOP = 265,
     OROR = 266,
     ANDAND = 267,
     CLASS = 268,
     PROGRAM = 269,
     LC = 270,
     RC = 271,
     LP = 272,
     RP = 273,
     LS = 274,
     RS = 275,
     WHILE = 276,
     FOR = 277,
     IF = 278,
     ELSE = 279,
     BREAK = 280,
     CONTINUE = 281,
     COMMA = 282,
     SEMICOLON = 283,
     RETURN = 284,
     CALLOUT = 285,
     EQUAL = 286,
     CHARACTER = 287,
     STRINGIT = 288,
     ID = 289,
     BOOLIT = 290,
     TYPE = 291,
     VOID = 292,
     MINUSEQUAL = 293,
     PLUSEQUAL = 294,
     HEXIT = 295,
     NUMBER = 296
   };
#endif


#ifndef YYSTYPE
typedef union YYSTYPE
{

/* Line 2663 of glr.c  */
#line 31 "parser.yy"

    char* string;
    int   integer;
    float val;
    char char_val_;
    Expression* expr_;
    ASTProgram* ast_;
  //  Field* field_;
    Method* method_;
    Variable* var_;
    vector <Variable*> *  variable_list_;
    vector <Expression*> *  expr_list_;
    vector<Fiemeth*> * fiemeth_list_;
    Statement* stmt_;
    vector<Statement*> * stmt_list_;
 //   Location* location_;
    Metharg* metharg_;
    Block* block_;
    vector<Vardec*> * var_decl_list_;
    Vardec* var_decl_;
    vector<Identifier*> * mvariables_;
    Literal* literal_;
    Methodcall* method_call_;
    Callarg* callout_arg_;
    vector <Callarg*> *  callout_arg_list_;
    vector <Expression*> *  method_call_arguments_;
    Intlit* int_literal_;
    Fiemeth* fiemeth_;
   // ASTProgram* MAIN;



/* Line 2663 of glr.c  */
#line 123 "parser.tab.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{

  char yydummy;

} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



extern YYSTYPE yylval;



