/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VOID = 258,
    EXTERN = 259,
    INT = 260,
    CHAR = 261,
    FOR = 262,
    WHILE = 263,
    SWITCH = 264,
    CASE = 265,
    DEFAULT = 266,
    BREAK = 267,
    IF = 268,
    ELSE = 269,
    TRUE = 270,
    FALSE = 271,
    CONSTANTE = 272,
    IDENTIFICATEUR = 273,
    LEQ = 274,
    GEQ = 275,
    EQ = 276,
    NOT = 277,
    GT = 278,
    LT = 279,
    LAND = 280,
    LOR = 281,
    NEQ = 282,
    STR = 283,
    PLUS = 284,
    MUL = 285,
    DIV = 286,
    MOINS = 287,
    UNARY = 288,
    INCLUDE = 289,
    RETURN = 290,
    OP = 291
  };
#endif
/* Tokens.  */
#define VOID 258
#define EXTERN 259
#define INT 260
#define CHAR 261
#define FOR 262
#define WHILE 263
#define SWITCH 264
#define CASE 265
#define DEFAULT 266
#define BREAK 267
#define IF 268
#define ELSE 269
#define TRUE 270
#define FALSE 271
#define CONSTANTE 272
#define IDENTIFICATEUR 273
#define LEQ 274
#define GEQ 275
#define EQ 276
#define NOT 277
#define GT 278
#define LT 279
#define LAND 280
#define LOR 281
#define NEQ 282
#define STR 283
#define PLUS 284
#define MUL 285
#define DIV 286
#define MOINS 287
#define UNARY 288
#define INCLUDE 289
#define RETURN 290
#define OP 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 67 "../final/parser.y"
 struct nom_variable { 
			char nom[100]; 
			struct noeud* nd;
			struct noeud_lcrs* nd_dot;
		} nd_obj;

		struct nom_variable2 { 
			char nom[100]; 
			struct noeud* nd;
			struct noeud_lcrs* nd_dot;
			char type[5];
		} nd_obj2; 

		struct nom_variable3 {
			char nom[100];
			struct noeud* nd;
			struct noeud_lcrs* nd_dot;
			char if_corps[5];
			char else_corps[5];
		} nd_obj3;
	

#line 152 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
