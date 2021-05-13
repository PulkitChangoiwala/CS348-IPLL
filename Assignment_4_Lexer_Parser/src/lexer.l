%{

/*

This code belongs to 
	Pulkit Changoiwala
	180101093
	changoiw@iitg.ac.in

*/
	#include<stdio.h>
	#include<string.h>
	//#include "token.h"
	#include "parser.tab.h"
	int yyline = 1;


%}

delm = [ \t]
whitespaces = {delm}+
digit = [0-9]
alphabets = [a-zA-Z]
underscore = [_]
identifier = {alphabets}({alphabets}|{digit}|{underscore})*
integer = {digit}+


%%

\n 				{yylineno++;}
"PROGRAM"		{return PROGRAM_Token;}
"VAR"			{return VAR_Token;}	
"BEGIN"			{return BEGIN_Token;}
"END"			{return END_Token;}
"END."			{return END__Token;}	
"INTEGER"		{return INTEGER_Token;}
"REAL"			{return REAL_Token;}
"FOR"			{return FOR_Token;}
"READ"			{return READ_Token;}
"WRITE"			{return WRITE_Token;}
"TO"			{return TO_Token;}
"DO"			{return DO_Token;}
";"				{return SEMICOLON_Token;}
":"				{return COLON_Token;}
","				{return COMMA_Token;}
":="			{return ASSIGN_Token;}
"+"				{return ADD_Token;}
"-"				{return SUBTRACT_Token;}
"*"				{return MULT_Token;}
"DIV"			{return DIV_Token;}
"("				{return BRACKET_O_Token;}
")"				{return BRACKET_C_Token;}
[a-zA-Z]([a-zA-Z0-9_])*	{yylval.str = strdup(yytext); return ID_Token;}
[0-9]+			{return INT_Token;}	
[ \t\n]			;
[0-9]+(\.[0-9]+)?(E[+-]?[0-9]+)? { return Real_Token;}	
.				printf("Character Is Invalid\n");

%%


//Auxiliary Functions

int yywrap(){
	return 1;
}

