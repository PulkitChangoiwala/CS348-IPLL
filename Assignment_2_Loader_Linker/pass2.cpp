#include "pass1.cpp"


struct exttable
{
	string cextsym;
	string extsym;
	string address;
	string length;

}ESTAB[20];



struct objectcode{
	string code;
	string address;
} obcode[500];


void pass2(){
	string temp, input;
	int num =0, inc = 0, record = 0, length = 0;
	

	//filestreams
	fstream f_input, f_ESTAB, f_output;
	f_input.open("input1.DAT", ios::in);
	f_ESTAB.open("ESTAB.DAT", ios::in);
	f_output.open("OUTPUT.DAT", ios::out);

	//Reading External Symbol Table
	while(!f_ESTAB.eof()){
		f_ESTAB>>ESTAB[num].cextsym>>ESTAB[num].extsym>>ESTAB[num].address>>ESTAB[num].length;
		num++;
	}



	string exeloc = ESTAB[0].address;
	string loc = exeloc;
	string start = loc;
	string st = start;
	string pstart, textloc, textlen;
	vector<string> mloc(30), mlen(30), label(50);

 	while(!f_input.eof()){
		f_input>>input;
		
		//Header Record
		if(input == "H"){ 
			f_input>>input;
			
			for(int i=0;i<num;++i){
				if(input==ESTAB[i].cextsym){ //Checking External Symbol Table
					pstart = ESTAB[i].address;
					break;
				}
			}

			while(input != "T") f_input>>input;
		}



		do{
			if(input == "T")
			{
				f_input>>textloc;
				textloc = Add_Hex(textloc, pstart);
				int textloc_dec = HexToDec(textloc), loc_dec = HexToDec(loc);
				

				for(int i=0; i<(textloc_dec - loc_dec); ++i){
					obcode[inc].code = "..";
					obcode[inc++].address = start;
					start = Add_Hex(start, "1");

				}


				f_input>>textlen;
				loc = Add_Hex(textloc , textlen);

			}

			else if(input == "M"){
				f_input>>mloc[record];
				mloc[record] = Add_Hex(mloc[record] , pstart);
				f_input>>mlen[record];
				f_input>>label[record++];

			}

			else{

				length = input.length();
				int x =0;
				
				for(int i=0; i<length; ++i){
					if(x==0){
						obcode[inc].code = "";
					}
					obcode[inc].code += input[i];
					x++;
					if(x>1){
						
						obcode[inc++].address = start;
						start = Add_Hex(start, "1");
						x =0;
					}
				}

			}

			f_input>>input;

		}while(input != "E");

		if(input == "E")
			f_input>>input;

	}



	string lbl = "";
	string address = "";
	string location;

	for(int n =0; n<record; ++n){
		char operation = label[n][0];
		length = label[n].length();
		lbl.clear();
		for(int i=1;i<length;++i){
			lbl += label[n][i];
		}
		length =0;
		location = Dec_TO_Hex(HexToDec(mloc[n])-HexToDec(exeloc));
		loc = location;
		int count = 0;
		int mlen_Dec = HexToDec(mlen[n]);
		address.clear();

		while(length <  mlen_Dec){

			string add1 = obcode[HexToDec(location)].code; 
			string add;
			map<char,int> mp = hex_value_of_dec();
			for(int i=0;i<add1.length();++i){
				if(mp.find(add1[i]) == mp.end()){ continue;}
				add+=add1[i];
			}
			address += add;
			location = Add_Hex(location, "1");
			count++;
			length += 2;

		}

								
		int i;
		for(i=0;i<num;++i){

			if(lbl == ESTAB[i].cextsym) break;
			if(lbl == ESTAB[i].extsym) break;
		}
		string new_address = "";
		switch(operation){
			case '+':   
						new_address = Add_Hex(address, ESTAB[i].address);
					 	break;
					

			case '-': new_address = Dec_TO_Hex(HexToDec(address) - HexToDec(ESTAB[i].address));
						break;
		}

		address.clear();
		address = new_address;
		
	
		
		int x = 0, y=0;
		
		while(count>0){
			if(x==0) {
				obcode[HexToDec(loc)].code = "";		
			}
			obcode[HexToDec(loc)].code += address[y++];
			x++;
			if(x>1){
				x =0; 
				loc = Add_Hex(loc, "1");
				count--;
			}
		}
	}
	


/*

**** Writing program to output file after Linking and Loading

*/
	int count =0;
	int n = 0;
	string s = Dec_TO_Hex(HexToDec(st) - 16);
	f_output<<s<<"\t";
	for(int i =1; i<=16; ++i){
		f_output<<"xx";
		if(i==4 || i==8 || i==12){
			f_output<<"\t";
		}
	}

	f_output<<"\n\n"<<obcode[0].address<<"\t";

	for(int i=0;i<inc;++i){
		f_output<<obcode[i].code;
		n++;
		if(n>3){
			f_output<<"\t";
			n=0;
			count++;
		}
		if(count>3){
			f_output<<"\n\n"<<obcode[i+1].address<<"\t";
			count = 0;
		}
	}


f_input.close();
f_ESTAB.close();
f_input.close();
	

}


signed main(){
pass1();
pass2();
return 0;
}