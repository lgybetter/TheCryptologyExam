#include <iostream>
#include <string>
#include <map>
#include <cmath>
using namespace std;

string add(string , string) ;
string mult(string , string);
string multInverse(string);
string _xor(string , string , int);
string chLenToMax(string , int);
string shift(string , int);
string* parseOneNum(string , int);
int discreteLogarithm(string);
int parseToDec(string);
string parseToBinary(int);
void setTable();
string appendStr(string,int);
string subStr(string,int);
bool  isFormat(string);
void showMenu();
map<int,string> tableReg;
map<string,int> tableArt;
map<int,string> tableInv;


const string m1 = "00011011";
const string m2 = "100011011";
const string g = "00000011";
const string multTable[] = {
	"00000010",
	"00000100",
	"00001000",
	"00010000",
	"00100000",
	"01000000",
	"10000000"
};


int main() {
	setTable();
	int op;
	bool exitFlag = false;
	bool correctFlag = true;
	do {
		showMenu();
		cout<<">>>";
		cin>>op;
		string a,b;
		switch(op) {
			case 0:
				cout<<"please input two binary numbers: "<<endl;
				cout<<">>>";
				cin>>a>>b;
				a = chLenToMax(a , 8);
				b = chLenToMax(b , 8);
				if(isFormat(a) && isFormat(b)) 
					cout<<a<<"+"<<b<<" : "<<add(a,b)<<endl;
				else {
					cout<<"the two binary numbers are unformat ! please restart again"<<endl;
					cout<<">>>";
				}
				continue;
			case 1:
				cout<<"please input two binary numbers: "<<endl;
				cout<<">>>";
				cin>>a>>b;
				a = chLenToMax(a , 8);
				b = chLenToMax(b , 8);
				if(isFormat(a) && isFormat(b)) 
					cout<<a<<"*"<<b<<" : "<<mult(a,b)<<endl;
				else {
					cout<<"the two binary numbers are unformat ! please restart again"<<endl;
					cout<<">>>";
				}
				continue;
			case 2:
				cout<<"please input one binary numbers: "<<endl;
				cout<<">>>";
				cin>>a;
				a = chLenToMax(a , 8);
				if(isFormat(a)) 
					cout<<"The multiplicative inverse of "<<a<<" is "<<multInverse(a)<<endl; 
				else {
					cout<<"the  binary number is unformat ! please restart again"<<endl;
					cout<<">>>";
				}
				continue;
			case 3:
				cout<<"please input one binary numbers: "<<endl;
				cout<<">>>";
				cin>>a;
				a = chLenToMax(a , 8);
				if(isFormat(a)) 
					cout<<"The discrete logarithm of "<<a<<" is "<<discreteLogarithm(a)<<endl; 
				else {
					cout<<"the  binary number is unformat ! please restart again"<<endl;
					cout<<">>>";
				}
				continue;
			case 4:
				exitFlag = true;
				continue;
			default:
				cout<<"the operation you input is incorrect ! please input again"<<endl;
				correctFlag = false;
				continue;
		}
	}while(!exitFlag);				
	return 0;
}


string add(string a , string b) {
	string c;
	c = _xor(a , b , 8);
	return c;
}

string mult(string a , string b) {
	map<string,string> list;
	string c = a;
	char h = c[0];
	for(int i = 0; i < 7; i ++) {
		if(h == '1') 
			c = _xor(shift(c , 8) , m1 , 8);
		else 
			c = shift(c , 8);		
		h = c[0];
		//cout<<multTable[i]<<"=>"<<c<<endl;
		list[multTable[i]] = c;
	}
	//cout<<"------------------------"<<endl;
	string * multList = parseOneNum(b,8);
	c = a;
	for(int i = 0; i < 8;i ++) {
		if(multList[i] != "") 
			c = _xor(c , list[multList[i]] , 8);
	}
	return c;
}

string multInverse(string a) {
	return tableInv[parseToDec(a)];
}

int discreteLogarithm(string x) {
	return tableArt[x];
}

string _xor(string a , string b , int len) {
	string c;
	for(int i = 0; i < len; i ++) {
		if(a[i] == b[i])
			c += "0";
		else
			c += "1";
	}
	return c;
}

string chLenToMax(string str , int maxLen) {
	int strLen = str.length();
	if(strLen <= 8)
		str = appendStr(str,maxLen);
	else 
		str = subStr(str,maxLen);
	return str;
}

string appendStr(string str, int maxLen) {
	int c = maxLen - str.length();
	string append;
	for(int i = 0; i < c; i ++)
		append += "0";
	str = append + str;
	return str;
}

string subStr(string str,int maxLen) {
	int strLen = str.length();
	return str.substr(strLen - maxLen,maxLen);
}

string shift(string str , int len) {
	for(int i = 0; i < len - 1; i ++)
		str[i] = str[i + 1];
	str[len - 1] = '0';
	return str;
}

string*  parseOneNum(string str , int len) {
	static string list[8];
	string append1,append2;
	for(int i = 0; i < len - 1; i ++) {
		if(str[i] == '1') {
			for(int j = 0; j < i; j ++) 
				append1 += "0";
			for(int j = 0; j < len - (i + 1); j ++)
				append2 += "0";
			list[i] = append1 + str[i] + append2;
			//cout<<list[i]<<endl;
			append2="";
			append1="";
		}
	}
	//cout<<"-------------------------------"<<endl;
	return list;
}

void setTable() {
	tableReg[0]=chLenToMax("1",8);
	for(int i = 1; i < 255; i ++)
		tableReg[i] = mult(tableReg[i - 1],g);
	for(int i = 0; i < 255; i ++)
		tableArt[tableReg[i]] = i;
	for(int i = 1; i < 256; i ++) {
		int k = tableArt[parseToBinary(i)];
		k = 255 - k;
		k %= 255;
		tableInv[i] = tableReg[k];
	}
}

int parseToDec(string str) {
	int sum = 0;
	for(int i = 0; i < str.length(); i ++)
		if(str[i] == '1')
			sum += pow(2,8-(i +1));
	return sum;
}

string parseToBinary(int num) {
	string str;
	int k = num;
	int m = num % 2;
	while(k != 1) {
		if(m == 0)
			str = "0" + str;
		else 
			str = "1" + str;
		k = k / 2;
		m = k % 2;
	}
	str = "1" + str;
	return str;
}

bool isFormat(string str) {
	for(int i = 0; i < str.length(); i ++) {
		if(str[i] != '1' && str[i] != '0')
			return false;
	}
	return true;
}

void showMenu() {
	cout<<"please choose the operation you want: "<<endl;
	cout<<"-------------------------------------------------------------------------"<<endl;
	cout<<"----------------------0. addition -----------------------------------"<<endl;
	cout<<"----------------------1. multiplication----------------------------"<<endl;
	cout<<"----------------------2. multiplicative inverse-----------------"<<endl;
	cout<<"----------------------3. discrete logarithm----------------------"<<endl;
	cout<<"----------------------4. exit-------------------------------------------"<<endl;
}