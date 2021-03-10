#include<bits/stdc++.h>
#include "Hexadecimal.cpp"
struct ESTAB{ //External Symbol Table
	string csname;
	string extsym;
	string address; //hexadecimal
	string length;  //hexadecimal
} es[20];

/*


*********************** PASS 1 STARTS ***********************


*/
void pass1(){
	string input, name, symbol;
	int count = 0, Progaddr, Csaddr, add, Len;
	string progaddr, csaddr, len; //address as hexadecimal number
	
	//File Streams
	fstream f_input, f_estab;
	f_input.open("input1.DAT", ios::in);
	f_estab.open("ESTAB.DAT", ios::out); 
	cout<<"\n Enter the address where program to be loaded: ";
	cin>>progaddr;
	csaddr = progaddr;
	

	f_input>>input;
	while(input != "END"){

		if(input == "H"){ //Header Record
			f_input>>name;
			es[count].csname = name;
			es[count].extsym = " ";
			string hex_addr;
			f_input>>hex_addr;
			es[count].address = Add_Hex(hex_addr, csaddr);
			f_input>>len; 
			es[count].length = len;
			f_estab<<es[count].csname<<" ** "<<es[count].address<<" "<<es[count].length<<"\n";
			count++;


		}


		else if(input == "D"){
			f_input>>input;
			while(input!="R"){
				es[count].csname = " ";
				es[count].extsym = input;
				string hex_addr;
				f_input>>hex_addr;
				es[count].address = Add_Hex(hex_addr, csaddr);
				es[count].length = "0";
				f_estab<<"** "<<es[count].extsym<<" "<<es[count].address<<" 0\n";
				count++;
				f_input>>input;


			}
			csaddr = Add_Hex(csaddr, len);

		}

		else if(input == "T"){

			while(input != "E")
				f_input>>input;

		}

		f_input>>input;
	}

	f_input.close();
	f_estab.close();

	//Printing ESTAB
	f_estab.open("ESTAB.DAT", ios::in);
	char ch;
	while(f_estab>>noskipws>>ch){
		
		cout<<ch;	
	}
	f_estab.close();

}



