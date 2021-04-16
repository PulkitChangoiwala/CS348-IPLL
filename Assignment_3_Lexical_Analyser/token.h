#define PROGRAM_Token	1
#define VAR_Token		2
#define BEGIN_Token		3
#define END_Token		4
#define END__Token		5
#define INTEGER_Token	6
#define FOR_Token		7
#define READ_Token		8
#define WRITE_Token		9
#define TO_Token		10
#define DO_Token		11
#define SEMICOLON_Token	12
#define COLON_Token		13
#define COMMA_Token		14
#define ASSIGN_Token	15
#define ADD_Token		16
#define SUBTRACT_Token	17
#define MULT_Token		18
#define DIV_Token		19
#define BRACKET_O_Token	20
#define BRACKET_C_Token	21
#define ID_Token		22
#define INT_Token		23


struct node
{
	int token_code;
	char* token;
	struct node* next;

}* hashtable[13];

int mod = 13;