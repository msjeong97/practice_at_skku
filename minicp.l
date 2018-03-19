%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minicp.tab.h"//refer to .y filename

#define SAVE_STR (yylval.str = strndup(yytext,yyleng))
#define SAVE_INTNUM (yylval.intnum = atoi(yytext))
#define SAVE_FLOATNUM (yylval.floatnum = atof(yytext))

int unary_binary_minus=0;// 0 for unary, 1 for binary
%}

unop \-
addiop [\+\-]
multop [\*\/]
relaop [<>]=?
eqltop [=!]=
id [A-Za-z_][A-Za-z0-9_]*
intnum [0-9]+
floatnum [0-9]+\.[0-9]+
space [ \t\r\n]

%%

"class"		{
	unary_binary_minus = 0;
	SAVE_STR;
	return CLASS;
}

"("			{
	unary_binary_minus = 0;
	SAVE_STR;
	return LPAREN;
}

")"			{
	unary_binary_minus = 1;
	SAVE_STR;
	return RPAREN;
}

"{"			{
	unary_binary_minus = 0;
	SAVE_STR;
	return LBRACE;
}

"}"			{
	unary_binary_minus = 0;
	SAVE_STR;
	return RBRACE;
}

"private"	{
	unary_binary_minus = 0;
	SAVE_STR;
	return PRIVATE;
}

"public"	{
	unary_binary_minus = 0;
	SAVE_STR;
	return PUBLIC;
}

"int"		{
	unary_binary_minus = 0;
	SAVE_STR;
	return INT;
}

"float"		{
	unary_binary_minus = 0;
	SAVE_STR;
	return FLOAT;
}

";"			{
	unary_binary_minus = 0;
	SAVE_STR;
	return SEMICOLON;
}

":"		{
	unary_binary_minus = 0;
	SAVE_STR;
	return COLON;
}

"="		{
	unary_binary_minus = 0;
	SAVE_STR;
	return EQUAL;
}

"."		{
	unary_binary_minus = 0;
	SAVE_STR;
	return DOT;
}

","		{
	unary_binary_minus = 0;
	SAVE_STR;
	return COMMA;
}

"main"		{
	unary_binary_minus = 0;
	SAVE_STR;
	return MAIN;
}

"["			{
	unary_binary_minus = 0;
	SAVE_STR;
	return LBRACK;
}

"]"			{
	unary_binary_minus = 0;
	SAVE_STR;
	return RBRACK;
}

"return"	{
	unary_binary_minus = 0;
	SAVE_STR;
	return RETURN;
}

"while"		{
	unary_binary_minus = 0;
	SAVE_STR;
	return WHILE;
}

"do"		{
	unary_binary_minus = 0;
	SAVE_STR;
	return DO;
}

"for"		{
	unary_binary_minus = 0;
	SAVE_STR;
	return FOR;
}

"if"		{
	unary_binary_minus = 0;
	SAVE_STR;
	return IF;
}

"else"		{
	unary_binary_minus = 0;
	SAVE_STR;
	return ELSE;
}

{unop}		{
	SAVE_STR;
	if(unary_binary_minus == 0){
		return UNOP;
	}else{
		unary_binary_minus = 0;
		return ADDIOP;
	}
}

{addiop}	{
	unary_binary_minus = 0;
	SAVE_STR;
	return ADDIOP;
}

{multop}	{
	unary_binary_minus = 0;
	SAVE_STR;
	return MULTOP;
}

{relaop}	{
	unary_binary_minus = 0;
	SAVE_STR;
	return RELAOP;
}

{eqltop}	{
	unary_binary_minus = 0;
	SAVE_STR;
	return EQLTOP;
}

{id}		{
	unary_binary_minus = 1;
	SAVE_STR;
	return ID;
}

{intnum}	{
	unary_binary_minus = 1;
	SAVE_STR;
	return INTNUM;
}

{floatnum}	{
	unary_binary_minus = 1;
	SAVE_STR;
	return FLOATNUM;
}

{space}		{
	;
}

.			{
	//unkown
}

%%
int print_check(){
	fprintf(stderr,"check");
	return 0;
}
