#include<bits/stdc++.h>
#include<fstream>
#include "Hexadecimal.cpp"

using namespace std;

/*
- Use g++ to compile the source code

- Keep the source code in a folder along with following files
	- Program.txt
	- OPTAB.txt
	- Hexadecimal.cpp
	All these three files are provided with the source code

- Run command g++ 180101093_Assign01.cpp in terminal
- Then execute with command ./a 
- Four Files will be created
	- Intermediate.txt
	- SYMTAB.txt
	- length.txt
	- Object_Program.txt

*/

int pass1();
int pass2();

int main(){
	pass1();
	pass2();
	return 0;
}



int pass1(){
	cout<<"Starting PASS 1\n";
	string line, label, opcode, operand;
	string locctr; int flag = 0;
	string start;
	fstream f_prog, f_symtab, f_inter, f_optab;

//Opening Different Files
	
	f_prog.open("Program.txt", ios::in);	//Open Assembly Code Program File
	if(!f_prog){ cout<<"Source File Is Missing!\n"; return 0;}
	f_optab.open("OPTAB.txt", ios::in);
	if(!f_optab){ cout<<"OPTAB Is Missing!\n"; return 0;}
	f_symtab.open("SYMTAB.txt", ios::trunc | ios::out | ios::in); //Opening Symbol Table File
	f_inter.open("Intermediate.txt", ios::out ); //Intermediate file which will be passed to Pass 2


//Reading First Line
	getline(f_prog, line);
	label = line.substr(0,10);
	opcode = line.substr(10,10);
	operand = line.substr(20);

	removeBackSpaces(label); removeBackSpaces(opcode); removeBackSpaces(operand);


//Setting Locctr, Location Counter
	if(opcode == "START"){

		//locctr = stoi(operand);
		locctr = operand;
		start = locctr;
		f_inter<<locctr;
		string writeLine = "\t"+label+"\t"+opcode+"\t"+operand;
		f_inter<<writeLine<<"\n";

	}
	else {
		locctr = "0";
	}


//Writing to Intermediate File

	while(!f_prog.eof()){


		getline(f_prog, line);
		if(line=="." || line == ";") continue;
		label = line.substr(0,10);
		opcode = line.substr(10,10);
		operand = line.substr(20);

		removeBackSpaces(label); removeBackSpaces(opcode); removeBackSpaces(operand);

		int count = (label.length() > 0) + (opcode.length() > 0) + (operand.length() > 0);
		
	//checking type of statement in assembler code

		if(label[0]!='.' && label[0] != ';') //Comment Line when Label is ; or .
		{
			
			if(count == 1){
				//cout<<"Ct 1\n";
				f_inter<<locctr;
				string writeLine = "\t\t"+opcode;
				f_inter<<writeLine<<"\n";


			}

			else if(count == 2){
				//cout<<"Ct 2\n";

				f_inter<<locctr;
				string writeLine = "\t\t"+opcode+"\t"+operand;
				f_inter<<writeLine<<"\n";

			}

			else if(count == 3){
				
				//cout<<"Label Exists\n";


				fstream temp_f;
				temp_f.open("SYMTAB.txt", ios::in);

				while(!temp_f.eof()){

					flag = 0;
					string symbol; int address;
					getline(temp_f, line);
					symbol = line.substr(0,10);
					removeBackSpaces(symbol);
					if(label == symbol){
						//symbol is duplicate
						flag = 1;
						cout<<"\n!!! Error: Duplicate Symbol Is Found\n";
						return 0;
					}

				}//end of Symbol Table
				temp_f.close();

					

				if(flag == 0){
					f_symtab<<label<<"\t"<<locctr<<"\n";
					f_inter<<locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<"\n";
				}

			}

	//Search Operation Code Table(OPTAB) for OPCODE		

			f_optab.seekg(0,ios::beg);
			while(!f_optab.eof()){

				getline(f_optab, line);
				string op_no = line.substr(line.length()-2,2); 
				
				string code = "";
				int itr=0; while(line[itr]!=' ' && line[itr]!='\t'){ code += line[itr++];} 

				//cout<<code<<"&"<<op_no<<endl;	

				if(opcode == code){
					locctr = Add_Hex(locctr, "3");
					flag =0;
					break;
				}

				else if(opcode == "WORD" || opcode == "word"){

					locctr = Add_Hex(locctr,"3");
					flag = 0;
					break;
				}

				else if(opcode == "RESW" || opcode == "resw"){	

					int Ressize = stoi(operand);
					string Hex = Dec_TO_Hex(Ressize);
					string temp = Add_Hex(Hex, Hex);
					temp = Add_Hex(temp, Hex);
					locctr = Add_Hex(temp,locctr);
					flag = 0;
					break;

				}

				else if(opcode == "RESB" || opcode == "resb"){

					int Ressize = stoi(operand);
					string Hex = Dec_TO_Hex(Ressize);
					locctr = Add_Hex(locctr, Hex);
					flag = 0;
					break;

				}
				else if(opcode == "BYTE" || opcode == "byte"){

					int oplen = operand.length()-3;

					if(operand[0] != 'C' && operand[0] !='X'){
						locctr = Add_Hex("1", locctr);
						flag = 0;
						break;
					}

					else if(opcode == "BYTE" && operand[0] == 'C'){

						locctr = Add_Hex(locctr, Dec_TO_Hex(oplen));
						flag = 0;
						break;
					}
					else if(opcode == "BYTE" && operand[0] == 'X'){
/*
						if(oplen%2!=0){
							locctr += oplen/2 + 1;
						}
						else locctr += oplen/2;*/
						locctr = Add_Hex(locctr, Dec_TO_Hex((oplen+1)/2));
						flag = 0;
						break;
					}
					else{
						flag = 1;
					}

				}// End of case when opcode is BYTE

				if(flag == 1)
				{
					cout<<opcode<<" Not Present in OPTAB\n";
					cout<<"!!! Exiting ... \n";
					return 0;
				}


			} //End of OPTAB while loop


		} //End of the case when line is not comment line

		if(opcode == "END")
		{
			break;
		}




	} //End of traversing of Program Text

	cout<<"\nCompleted the Generation of SYMTAB\n";

	fstream f_length;  f_length.open("length.txt", ios::out);
	int length = HexToDec(locctr) - HexToDec(start);
	f_length<<Dec_TO_Hex(length);
	f_prog.close(); f_inter.close(); f_symtab.close(); f_optab.close();
	f_length.close();

	cout<<"\nEnding PASS 1\n";
	
	

return 1;

}

/*********************************************************************

*********************************PASS 2 Starts Here ****************************

*********************************************************************/


int pass2(){

	cout<<"Starting PASS 2\n";
	fstream f_symtab, f_inter, f_optab, f_obj, f_length;
	string start, line, target = "0";
	int j =0;
	long int bseek, aseek; int newText=0;

//Opening Different Files
	
	f_optab.open("OPTAB.txt", ios::in);
	if(!f_optab){ cout<<"OPTAB Is Missing!\n"; return 0;}
	f_symtab.open("SYMTAB.txt", ios::in); //Opening Symbol Table File
	if(!f_symtab){ cout<<"SYMTAB Is Missing!\n"; return 0;}
	f_inter.open("Intermediate.txt", ios::in ); //Intermediate file which will be passed to Pass 2
	if(!f_inter){ cout<<"Intermediate Is Missing!\n"; return 0;}
	f_length.open("length.txt", ios::in);
	if(!f_length){ cout<<"Length file Is Missing!\n"; return 0;}
	f_obj.open("Object_Program.txt", ios::out);



	
	string locctr, label, opcode, operand;
	string opcode_no="";
	f_inter>>locctr>>label>>opcode>>operand;
	//cout<<locctr<<label<<endl;

	if(opcode == "START"){
		start = operand;
		string length;
		f_length>>length;
		f_obj<<"H^"<<label;
		for(int i=label.size();i<6;++i){f_obj<<" ";}
		f_obj<<"^00"<<start<<"^00"<<length;
		f_obj<<"\nT^00"<<start<<"^00^";
		bseek = f_obj.tellg();


	}
	
	getline(f_inter, line); //removing "\n" 
	int count = 0;


//Start Reading INtermediate File
	while(!f_inter.eof()){

		getline(f_inter, line);
		istringstream ss(line);
		label = ""; locctr = ""; opcode = ""; operand ="";
		ss>>locctr>>label>>opcode>>operand;
		//cout<<locctr<<label<<opcode<<operand<<endl;
		int ct = (locctr.length()>0)+(label.length() > 0) + (opcode.length() > 0) + (operand.length() > 0);
	 	
	 	//ct is number of words
	 	if(ct == 2){
	 		opcode = label;
	 		label = "";
	 	}

	 	else if(ct == 3){
	 		operand = opcode;
	 		opcode = label;
	 		label = "";
	 	}




//Check if New Text Record To Be started
	 	
		if(newText || count>= 60 || opcode == "RESB" || opcode == "RESW" ||opcode == "END"){
			aseek = f_obj.tellg();
	 		f_obj.seekg(-(aseek-bseek)-3L, ios::cur);
	 		int record_len = count/2; //
	 		if(record_len<16) f_obj<<"0"<<Dec_TO_Hex(record_len)<<"^";
	 		else f_obj<<Dec_TO_Hex(record_len)<<"^";

	 		f_obj.seekg(0,ios::end);
	 		
	 		if(opcode == "END") {break;}
	 		newText=1;
	 		if(opcode != "RESW" && opcode != "RESB" && newText){
	 			f_obj<<"\nT^00"<<locctr<<"^00^";
	 			newText = 0;
	 		}

	 		bseek = f_obj.tellg();
	 		count = 0;

	 	}




//Search in OPTABLE 

	 	f_optab.seekg(0, ios::beg);
	 	int op_status = 0;
	 
	 	while(!f_optab.eof()){
	 		string code, op_no;
	 		f_optab>>code>>op_no;
	 		//cout<<code<<" * "<<op_no;
	 		if(code == opcode){ //Found in OPTAB
	 			opcode_no = op_no;
	 			op_status = 1;
	 			break;
	 		}
	 	}







//Case When Symbol is BUFFER
	 	j = operand.length();
	 	if(op_status == 1 && operand[j-1] == 'X' && operand[j-2] == ','){

	 		j = operand.length();
	 		operand = operand.substr(0, j-2);
	 		f_symtab.seekg(0,ios::beg);
	 		string symbol; string address;
	 		while(!f_symtab.eof()){
	 			f_symtab>>symbol>>address;
	 			if(symbol == operand){
	 				target = address; //For SYMBOL == BUFFER 1039
	 				target = Add_Hex(target, "8000");
	 				break;	
	 			}
	 		}
	 		f_obj<<opcode_no;
	 		for(int i=target.length();i<4;++i) f_obj<<" ";
	 		f_obj<<target<<"^";
	 		count+=6;
	 		continue;
	 	}




//CASE 2
	 	else if(op_status == 1 && opcode != "RSUB"){

	 		f_symtab.seekg(0,ios::beg);
	 		string symbol; string address;
	 		while(!f_symtab.eof()){
	 			f_symtab>>symbol>>address;
	 			if(symbol == operand){
	 				target = address;
	 				break;	
	 			}
	 		}
	 		f_obj<<opcode_no;
	 		for(int i=target.length();i<4;++i) f_obj<<" ";
	 		f_obj<<target<<"^";
	 		count+=6;
	 		continue;

	 	}



//CASE 3

	 	else if(op_status == 1 && opcode == "RSUB"){
	 		f_obj<<opcode_no<<"0000^";
	 		count +=6;
	 		continue;
	 	}




//CASE 4
	 	else{

	 		//CASE 4.1
	 		if(opcode == "BYTE" || opcode == "byte"){
	 			
		 			string ascii;

		 			//CASE 4.1.1
		 			if(operand[0] == 'C'){
		 				for(int i=2; i<operand.length()-1; ++i){
		 					ascii += Dec_TO_Hex((int)operand[i]);

		 				}
		 				f_obj<<ascii<<"^";
		 				count += operand.length()-3;	 				

		 			}


		 			//CASE 4.1.2
		 			else if(operand[0] == 'X'){

		 				for(int i=2; i<operand.length()-1; ++i){
		 					f_obj<<operand[i];

		 				}
		 				f_obj<<"^";
		 				count += operand.length()-3;

		 			}	


	 		}

	 		//CASE 4.2	
	 		else if(opcode == "WORD" || opcode == "word"){
	 			string hex = Dec_TO_Hex(stoi(operand));
	 			int len = hex.length();
	 			for(int i = len; i<6; ++i){
	 				f_obj<<"0";
	 			}
	 			f_obj<<hex<<"^";
	 			count+=6;
	 			continue;

	 		}



	 		//CASE 4.3: RESW, RESB
	 		else {
	 			continue;
	 		}
	 	
	 	
	 	} //Case 4 ENDS





	}



	f_obj<<"\nE^00"<<start;



	f_inter.close(); f_symtab.close(); f_optab.close(); f_obj.close(); f_length.close();
	
	cout<<"\nEnding PASS 2\n";
	return 1;
}