#include<bits/stdc++.h>
#include<fstream>

using namespace std;



map<char, int> hex_value_of_dec(void)
{
    // Map the values to decimal values
    map<char, int> m{ { '0', 0 }, { '1', 1 }, 
                      { '2', 2 }, { '3', 3 }, 
                      { '4', 4 }, { '5', 5 }, 
                      { '6', 6 }, { '7', 7 }, 
                      { '8', 8 }, { '9', 9 }, 
                      { 'A', 10 }, { 'B', 11 }, 
                      { 'C', 12 }, { 'D', 13 }, 
                      { 'E', 14 }, { 'F', 15 } };
 
    return m;
}
 
// Map for converting decimal values
// to hexadecimal
map<int, char> dec_value_of_hex(void)
{
    // Map the values to the
    // hexadecimal values
    map<int, char> m{ { 0, '0' }, { 1, '1' }, 
                      { 2, '2' }, { 3, '3' }, 
                      { 4, '4' }, { 5, '5' }, 
                      { 6, '6' }, { 7, '7' }, 
                      { 8, '8' }, { 9, '9' }, 
                      { 10, 'A' }, { 11, 'B' }, 
                      { 12, 'C' }, { 13, 'D' }, 
                      { 14, 'E' }, { 15, 'F' } };
 
    return m;
}
 
string Dec_TO_Hex(int n){

	string hex;
    int i = 0; 
    if(n==0) return "0";
    
    while(n!=0) 
    {    
        int temp  = 0; 
        temp = n % 16;   
        if(temp < 10) 
        { 
            hex += (char)(temp + 48); 
            i++; 
        } 
        else
        { 
            hex  += (char)(temp + 55); 
            i++; 
        } 
          
        n = n/16; 
    } 
      
    reverse(hex.begin(),hex.end());  
    return hex; 

}

int HexToDec(string s){

	int n = s.length()-1;
	map<char, int> m = hex_value_of_dec();
    int ans =0;
	int cnt=0;
	while(n>=0){
		int t = m[s[n]];
		n--;
		ans += t*((int)pow(16,cnt++));
	}
	return ans;
}

// Function to add the two hexadecimal numbers
string Add_Hex(string a, string b)
{
    map<char, int> m = hex_value_of_dec();
    map<int, char> k = dec_value_of_hex();
 
    // Check if length of string first is
    // greater than or equal to string second
    if (a.length() < b.length())
        swap(a, b);
 
    // Store length of both strings
    int l1 = a.length(), l2 = b.length();
 
    string ans = "";
 
    // Initialize carry as zero
    int carry = 0, i, j;
 
    // Traverse till second string
    // get traversal completely
    for (i = l1 - 1, j = l2 - 1;
         j >= 0; i--, j--) {
 
        // Decimal value of element at a[i]
        // Decimal value of element at b[i]
        int sum = m[a[i]] + m[b[j]] + carry;
 
        // Hexadecimal value of sum%16
        // to get addition bit
        int addition_bit = k[sum % 16];
 
        // Add addition_bit to answer
        ans.push_back(addition_bit);
 
        // Update carry
        carry = sum / 16;
    }
 
    // Traverse remaining element
    // of string a
    while (i >= 0) {
 
        // Decimal value of element
        // at a[i]
        int sum = m[a[i]] + carry;
 
        // Hexadecimal value of sum%16
        // to get addition bit
        int addition_bit = k[sum % 16];
 
        // Add addition_bit to answer
        ans.push_back(addition_bit);
 
        // Update carry
        carry = sum / 16;
        i--;
    }
 
    // Check if still carry remains
    if (carry) {
        ans.push_back(k[carry]);
    }
 
    // Reverse the final string
    // for desired output
    reverse(ans.begin(), ans.end());
 
    // Return the answer
    return ans;
}
 
void removeBackSpaces(string &s){
	while(s.back() == ' ') {
		s.pop_back();
	}
	return;
}

