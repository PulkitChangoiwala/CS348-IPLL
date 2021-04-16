%{
	#include<stdio.h>
	#include<string.h>
	#include "token.h"

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
[a-zA-Z]([a-zA-Z0-9_])*	{return ID_Token;}
[0-9]+			{return INT_Token;}	
[ \t\n]			;	
.				printf("Character Is Invalid\n");

%%


//Auxiliary Functions

int yywrap(){
	return 1;
}


// *** Function To Hash Values *** //

int hash_value(char* key){
	int sum = 0;
	int i = 0;
	while(1){
		if(key[i]=='\0') break;
		sum *= 101;
		sum += (key[i] >= 'A' && key[i] <='Z') ? (key[i] - 'A') : (key[i]-'0');
		sum %= mod;
		i++;
	}
	return sum;
}






// *** Inserts Given Token Code and Corresponding Token in Hashtable *** //

void insert_in_hashtable(int token_code, char* token){
	
	int hashtable_ind = hash_value(token);
	struct node* itr = hashtable[hashtable_ind];

	//Create a node for the token
	struct node* token_temp = (struct node*) malloc(sizeof(struct node));
	token_temp -> token_code = token_code;
	token_temp -> token = token;
	token_temp -> next = NULL;

	
	if(itr){
		//Traverse to the last of the list
		while(itr->next)
			itr = itr->next;
		itr -> next = token_temp;
	}
	else {
		hashtable[hashtable_ind] = token_temp;
	}
	return;
}





// *** search a token in the hashtable *** //

int search_in_hashtable(char* token)
{
	int found  = 0;	
    int hashtable_ind = hash_value(token);
    struct node* itr = hashtable[hashtable_ind];
  
  	// Traverse The List
    while(itr != NULL)
    {
        if(!strcmp(token, itr->token)){
        	found = 1;
        	break;
        }
    
        itr = itr->next;
    }

    return found;
}






// *** procedure to install the lexeme in the hashtable *** //

void install_id(int token_code, char* token)
{	
	if(!search_in_hashtable(token))
    	insert_in_hashtable(token_code, token);
}




// *** procedure to install the lexeme in the hashtable *** //

void install_num(int token_code, char* token)
{	
	if(!search_in_hashtable(token))
    	insert_in_hashtable(token_code, token);
}




int main(){
	
	FILE *prog_file = fopen("program.pas", "r");
	int token_code, curr_line =0;
	if(!prog_file){
		printf("!!Error Opening File!! \n");
		exit(1);
	}

	for(int i = 0; i < mod; ++i){
		hashtable[i] = NULL;
	}

	yyin = prog_file; 		//Set Input Stream Pointer
	token_code = yylex();	//Token Code for lexeme currently being read
	
	while(1){
		if(!token_code)
			return 0;

		// Printing the line number of the source program
		if(curr_line != yylineno){ 
			curr_line = yylineno;
			printf("%d", yylineno);
		}

		//Printing the token code
		printf("\t\t%d\t\t", token_code);


	 	// yytext is not an identifier or a number
	    if(token_code < 22)
	    {
	        printf("\n");
	        token_code = yylex();
	    }


	    // yytext is an identifier
	    else if(token_code == 22)
	    {
	        install_id(token_code, yytext); // install id in hashtable
	        printf("^%s\n", yytext);
	        token_code = yylex();
	    }


	    // if yytext is a num
	    else if(token_code == 23)
	    {
	        install_num(token_code, yytext); // install num in hashtable
	        printf("#%s\n", yytext);
	        token_code = yylex();
	    }

	}

    return 0;
}