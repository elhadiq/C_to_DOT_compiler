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
    THEN = 268,
    IF = 269,
    ELSE = 270,
    TRUE = 271,
    FALSE = 272,
    CONSTANTE = 273,
    IDENTIFICATEUR = 274,
    LEQ = 275,
    GEQ = 276,
    EQ = 277,
    NOT = 278,
    GT = 279,
    BAND = 280,
    BOR = 281,
    LSHIFT = 282,
    RSHIFT = 283,
    LT = 284,
    LAND = 285,
    LOR = 286,
    NEQ = 287,
    STR = 288,
    PLUS = 289,
    MUL = 290,
    DIV = 291,
    MOINS = 292,
    UNARY = 293,
    INCLUDE = 294,
    RETURN = 295,
    OP = 296,
    REL = 297
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
#define THEN 268
#define IF 269
#define ELSE 270
#define TRUE 271
#define FALSE 272
#define CONSTANTE 273
#define IDENTIFICATEUR 274
#define LEQ 275
#define GEQ 276
#define EQ 277
#define NOT 278
#define GT 279
#define BAND 280
#define BOR 281
#define LSHIFT 282
#define RSHIFT 283
#define LT 284
#define LAND 285
#define LOR 286
#define NEQ 287
#define STR 288
#define PLUS 289
#define MUL 290
#define DIV 291
#define MOINS 292
#define UNARY 293
#define INCLUDE 294
#define RETURN 295
#define OP 296
#define REL 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 84 "parser.y"
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
	

#line 164 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
