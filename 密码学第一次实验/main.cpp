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

//用在乘法中进行1B异或
const string m1 = "00011011";
//输入的生成元
string g;
//保存在乘法中进行每一次的异或对应的键
const string multTable[] = {
	"00000001",
	"00000010",
	"00000100",
	"00001000",
	"00010000",
	"00100000",
	"01000000",
	"10000000"
};


int main() {
	
	int n1;
	bool correctFlag2 = true;
	do {
		n1 = 3;
		g = chLenToMax(parseToBinary(n1),8);
		if(!isFormat(g)) {
			cout<<"the generator you input is unformat ! please input again"<<endl;
			correctFlag2 = false;
			cout<<">>>";
		} else {
			correctFlag2 = true;
		}
	}while(!correctFlag2);
	setTable();
	int op;
	bool exitFlag = false;
	bool correctFlag = true;
	do {
		showMenu();
		cout<<">>>";
		cin>>op;
		string a,b;
		int n2,n3;
		switch(op) {
			case 0:
				cout<<"please input two numbers: "<<endl;
				cout<<">>>";
				cin>>n2>>n3;
				a = chLenToMax(parseToBinary(n2) , 8);
				b = chLenToMax(parseToBinary(n3) , 8);
				if(isFormat(a) && isFormat(b)) 
					cout<<n2<<"+"<<n3<<" : "<<parseToDec(add(a,b))<<endl;
				else {
					cout<<"the two  numbers are unformat ! please restart again"<<endl;
					cout<<">>>";
				}
				continue;
			case 1:
				cout<<"please input two  numbers: "<<endl;
				cout<<">>>";
				cin>>n2>>n3;
				a = chLenToMax(parseToBinary(n2) , 8);
				b = chLenToMax(parseToBinary(n3) , 8);
				if(isFormat(a) && isFormat(b)) 
					cout<<n2<<"*"<<n3<<" : "<<parseToDec(mult(a,b))<<endl;
				else {
					cout<<"the two  numbers are unformat ! please restart again"<<endl;
					cout<<">>>";
				}
				continue;
			case 2:
				cout<<"please input one  numbers: "<<endl;
				cout<<">>>";
				cin>>n2;
				a = chLenToMax(parseToBinary(n2) , 8);
				if(isFormat(a)) 
					cout<<"The multiplicative inverse of "<<n2<<" is "<<parseToDec(multInverse(a))<<endl; 
				else {
					cout<<"the  number is unformat ! please restart again"<<endl;
					cout<<">>>";
				}
				continue;
			case 3:
				cout<<"please input a generator: "<<endl;
				cout<<">>>";
				cin>>n1;
				g = chLenToMax(parseToBinary(n1),8);
				setTable();
				cout<<"please input one numbers: "<<endl;
				cout<<">>>";
				cin>>n2;
				a = chLenToMax(parseToBinary(n2) , 8);
				if(isFormat(a)) 
					cout<<"The discrete logarithm of "<<n2<<" is "<<discreteLogarithm(a)<<endl; 
				else {
					cout<<"the  number is unformat ! please restart again"<<endl;
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


//加法操作，简单异或
string add(string a , string b) {
	string c;
	c = _xor(a , b , 8);
	return c;
}

//乘法操作
string mult(string a , string b) {
	//建立一个映射，用于保存每一次移位对应的结果
	map<string,string> list;
	string c = a;
	//用来获取最高位
	char h = c[0];
	for(int i = 0; i < 8; i ++) {
		//第一次乘以"00000001"，结果相当于本身
		if(i == 0) 
			c = a;
		else {
			//如果最高位为1,先移位后异或1B
			if(h == '1') 
				c = _xor(shift(c , 8) , m1 , 8);
			//最高位不是1,直接进行移位
			else 
				c = shift(c , 8);	
		}	
		h = c[0];
		//cout<<multTable[i]<<"=>"<<c<<endl;
		//保存对应的键值对
		list[multTable[i]] = c;
	}
	//cout<<"------------------------"<<endl;
	//获取b中位数为1对应的数值
	string * multList = parseOneNum(b,8);
	c = "00000000";
	//cout<<c<<"xor";
	for(int i = 0; i < 8;i ++) {
		if(multList[i] != "") {
			//进行乘法操作
			//cout<<list[multList[i]]<<"xor";
			c = _xor(c , list[multList[i]] , 8);
		}
	}
	// cout<<endl;
	return c;
}

//乘法逆元操作
string multInverse(string a) {
	return tableInv[parseToDec(a)];
}

//进行获取离散对数操作
int discreteLogarithm(string x) {
	return tableArt[x];
}

//定义二进制的异或操作
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

//把二进制数据格式化为8位数二进制
string chLenToMax(string str , int maxLen) {
	int strLen = str.length();
	if(strLen <= 8)
		str = appendStr(str,maxLen);
	else 
		str = subStr(str,maxLen);
	return str;
}

//当位数小于8位，对数据进行前面补0操作
string appendStr(string str, int maxLen) {
	int c = maxLen - str.length();
	string append;
	for(int i = 0; i < c; i ++)
		append += "0";
	str = append + str;
	return str;
}


//位数大于8位，获取后8位操作
string subStr(string str,int maxLen) {
	int strLen = str.length();
	return str.substr(strLen - maxLen,maxLen);
}

//进行移位操作
string shift(string str , int len) {
	for(int i = 0; i < len - 1; i ++)
		str[i] = str[i + 1];
	str[len - 1] = '0';
	return str;
}

//分析一个二进制数据中有多少个1，返回相应的数组
string*  parseOneNum(string str , int len) {
	static string list[8];
	for(int i = 0; i < 8; i ++) {
		list[i] = "";
	}
	string append1,append2;
	for(int i = 0; i < len; i ++) {
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


//建立对应的生成元的正表，反表，逆表
void setTable() {
	tableReg[0]=chLenToMax("1",8);
	for(int i = 1; i < 255; i ++)
		tableReg[i] = mult(tableReg[i - 1],g);
	for(int i = 0; i < 255; i ++)
		tableArt[tableReg[i]] = i;
	for(int i = 1; i < 256; i ++) {
		int k = tableArt[chLenToMax(parseToBinary(i),8)];
		k = 255 - k;
		k %= 255;
		tableInv[i] = tableReg[k];
	}
}

//把二进制转化为十进制
int parseToDec(string str) {
	int sum = 0;
	for(int i = 0; i < str.length(); i ++)
		if(str[i] == '1')
			sum += pow(2,8-(i +1));
	return sum;
}

//把十进制转化为二进制
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

//判断二进制数据是否只含有1或0
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
