%{
/*

This code belongs to 
	Pulkit Changoiwala
	180101093
	changoiw@iitg.ac.in

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"


int is_successful = 1;
int assignment_cnt = 0;
int exp_type[100];
void yyerror(char const *s);

int is_valid_identifier(char *s);

int yylex(void);
extern int helper_main();
extern int yylineno;
extern char * yytext;




//hashtable


	struct node
	{
		int token_code;
		char* token;
		int type_id;
		struct node* next;

	}* hashtable[13];

	int mod = 13;


int hash_value(char *s);
int search_in_hashtable(char *);
void insert_in_hashtable(int , char *);
void print_hashtable();
void install_num(int , char*);
void install_id(int , char*);
void set_type(int s);
int has_type(char* s);

%}


%union {char* str; int num; char id; char arr[25]; } 
%start prog
%type <str> dec_id_list


%token PROGRAM_Token 
 VAR_Token
 BEGIN_Token		
 END_Token		
 END__Token		
 INTEGER_Token
 REAL_Token	
 FOR_Token		
 READ_Token		
 WRITE_Token		
 TO_Token		
 DO_Token		
 SEMICOLON_Token	
 COLON_Token		
 COMMA_Token		
 ASSIGN_Token	
 ADD_Token		
 SUBTRACT_Token	
 MULT_Token		
 DIV_Token		
 BRACKET_O_Token	
 BRACKET_C_Token	
<str> ID_Token		
<integer> INT_Token
<float> Real_Token

%nonassoc '='
%left '+' '-'
%left '*' '/'
%left UNEG UPOS

%%

prog 			:  PROGRAM_Token prog_name VAR_Token dec_list BEGIN_Token    
				   stmt_list END__Token {;}
				;

prog_name 		: ID_Token {;}	

dec_list 		: dec {;}
 				| dec_list SEMICOLON_Token dec {;}
 			
 				; 

dec 			: dec_id_list type {	

								yyerrok;
								char msg[100] ="Missing A Colon";
								yyerror(msg);
								printf(" :: At Line No %d, Add Colon\n", yylineno);

							}

				| dec_id_list COLON_Token {
									yyerrok;
									char msg[100] ="Missing Type Name";	
									yyerror(msg);
									printf(" :: At Line No %d, Add Type Of The Variables\n", yylineno);

					}
						
				
				| dec_id_list COLON_Token type {;}
				| error dec {

							yyerrok;
							char msg[100] ="Missing SEMICOLON";	
							yyerror(msg);
							printf(" :: At Line No %d, Add SEMICOLON\n", yylineno);							

				}
				;
	            

type 			: INTEGER_Token {set_type(INTEGER_Token);}
				| REAL_Token {set_type(REAL_Token);}
				;

dec_id_list 	: ID_Token {
				  if(search_in_hashtable($1)){
						yyerrok;
						char msg[100] ="Multiple Declaration Of The Variable";	
						yyerror(msg);
						printf(" :: At Line No %d, Remove Multiple Declarations\n", yylineno);							

					}
					else 
						install_id(ID_Token, $1);
				} 

				| dec_id_list ID_Token {
							yyerrok;
							char msg[100] ="Variable Names Are Not Separated With Comma";	
							yyerror(msg);
							printf(" :: At Line No %d, Add Comma Between Variable Names \n", yylineno);		
				}

				| dec_id_list COMMA_Token ID_Token {
					if(search_in_hashtable($3)){
									yyerrok;
									char msg[100] ="Multiple Declaration Of The Variable";	
									yyerror(msg);
									printf(" :: At Line No %d, Remove Multiple Declarations\n", yylineno);							

					}
					else
						install_id(ID_Token, $3);
				}
				;



id_list 		: ID_Token {;} 
				| id_list ID_Token {
							yyerrok;
							char msg[100] ="Identifiers Names Are Not Separated With Comma";	
							yyerror(msg);
							printf(" :: At Line No %d, Add Comma Between Variable Names \n", yylineno);		
				}
				| id_list COMMA_Token ID_Token {;}
				;

stmt_list 		: stmt {;}
		  		| stmt_list SEMICOLON_Token stmt {;}
		  	
		  		;

stmt 			: assign {;}
				| read {;}
				| write {;}
				| for {;}
				| error stmt 
					{	

						yyerrok;
						char msg[100] ="Missing SEMICOLON";	
						yyerror(msg);
						printf(" :: At Line No %d, Add SEMICOLON\n", yylineno);							

					}
				;


assign 			:  ID_Token ASSIGN_Token exp {	
						
						if(!search_in_hashtable($1)){

									yyerrok;
									char msg[100] ="Undeclared Variables";	
									yyerror(msg);
									printf(" :: At Line No %d, Declare Variable\n", yylineno);							

							}
							else {


								if(exp_type[assignment_cnt] == -1 || has_type($1) != exp_type[assignment_cnt]){

									yyerrok;
									char msg[100] ="Type Mismatch";	
									yyerror(msg);
									printf(" :: At Line No %d, Type Is Not Matching Across Assignment Operator\n", yylineno);							

								}
							}
							assignment_cnt++;
				}
	   			;

exp 			: term {;}
				| exp ADD_Token term {;}
				| exp SUBTRACT_Token term {;}
				;

term 			: factor {;}
				| term MULT_Token factor {;}
				| term DIV_Token factor {;}
				; 

factor 			: ID_Token {
					int typeId = has_type($1);
					if(exp_type[assignment_cnt]==0){
						exp_type[assignment_cnt] = typeId ;
					}
					else if(exp_type[assignment_cnt]!=-1 && exp_type[assignment_cnt] != typeId){
						exp_type[assignment_cnt] = -1;
					}

				}

			    | INT_Token {
			    	int typeId = INTEGER_Token;
			    	if(exp_type[assignment_cnt]==0){
							exp_type[assignment_cnt] = typeId ;
					}
					else if(exp_type[assignment_cnt]!=-1 && exp_type[assignment_cnt] != typeId){
							exp_type[assignment_cnt] = -1;
					}
					
				}


			    | Real_Token {

			    	int typeId = REAL_Token;
				    if(exp_type[assignment_cnt]==0){
							exp_type[assignment_cnt] = typeId ;
						}
					else if(exp_type[assignment_cnt]!=-1 && exp_type[assignment_cnt] != typeId){
						
							exp_type[assignment_cnt] = -1;
						}
				
			    }
			    | BRACKET_O_Token exp BRACKET_C_Token {;}
			    ;	  

read 			: READ_Token BRACKET_O_Token id_list BRACKET_C_Token {;}
	 			;

write 			: WRITE_Token BRACKET_O_Token id_list BRACKET_C_Token {;}
	  			;	

for 			: FOR_Token index_exp DO_Token body {}
				;

index_exp 		: ID_Token ASSIGN_Token exp TO_Token exp {;}
		  		;

body 			: stmt {;}
	 			| BEGIN_Token stmt_list END_Token {;}
	 			;	 



%%
/*C code*/

// *** Function To Hash Values *** //
int is_valid_identifier(char* s){
	int temp = 0;
	temp = strcmp(s, "PROGRAM") || strcmp(s, "VAR") || strcmp(s, "BEGIN") || strcmp(s, "END") || strcmp(s, "INTEGER") || strcmp(s, "REAL") || strcmp(s, "FOR") || strcmp(s, "READ") || strcmp(s, "WRITE") || strcmp(s, "TO") || strcmp(s, "DO") || strcmp(s, "DIV");
	return temp;
}
int hash_value(char* key){
	int sum = 0;
	int i = 0;
	while(1){
		if(key[i]=='\0') break;
		sum *= 101;
		sum += (key[i] >= 'A' || key[i] <='Z') ? (key[i] - 'A') : (key[i]-'0');
		sum %= mod;
		i++;
	}
	return sum;
}


//  *** Printing Hashtable *** //
void print_hashtable(){

	struct node* itr;
	for(int i=0; i< mod; ++i){
		itr = hashtable[i];
		while(itr){
			printf("%s ** %d || ", itr->token, itr -> type_id);
			itr = itr->next;
		}
		printf("\n");
	}
}




// *** Inserts Given Token Code and Corresponding Token in Hashtable *** //

void insert_in_hashtable(int token_code, char* token){
	
	int hashtable_ind = hash_value(token);
	struct node* itr = hashtable[hashtable_ind];
	//Create a node for the token
	struct node* token_temp = (struct node*) malloc(sizeof(struct node));
	token_temp -> token_code = token_code;
	token_temp -> token = token;
	token_temp -> type_id =  0;
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




//Set Type to variables whose type is not set till now
void set_type(int type_token){
	
	struct node* itr;
	for(int i=0; i<mod; ++i){
		itr = hashtable[i];
		while(itr) {
			if(!(itr -> type_id) ) itr->type_id = type_token;
			itr = itr->next;
		}
	}
	return;
}


//find type of identifier
int has_type(char* token){
	
	int typeId = -1;
	int hashtable_ind = hash_value(token);
    struct node* itr = hashtable[hashtable_ind];

    // Traverse The List
    while(itr != NULL)
    {
        if(!strcmp(token, itr->token)){
        	typeId = itr -> type_id;
        	break;
        }
    
        itr = itr->next;
    }

    return typeId;


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




int main(void) {

	yyparse();
	if(is_successful){
		printf(ANSI_COLOR_GREEN "Parsing Is Done & It is Successful\n" ANSI_COLOR_RESET);
	}
	else {
		printf(ANSI_COLOR_MAGENTA "!!! Parsing is not successful !!!\n" ANSI_COLOR_RESET);
	}

	return 0;

}

void yyerror(char const *s) {
	
	

	printf(ANSI_COLOR_RED "\nERROR: " ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET"\n--------------------------\n", s);
	is_successful = 0;
	return;
}