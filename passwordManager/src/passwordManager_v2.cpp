#include<iostream>
#include<ctime>
#include<string>
#include<fstream>
#include <stdlib.h>
#include "sha256.h"
using namespace std;



string generatePass(){
	srand(time(NULL));
	string password="";
	for(int i=0;i<20;i++){
		///int i=0;
		//for(i;i<20;i++){
		int e=rand()%26+65;
		int f=rand()%26+97;
		int q=rand()%10+48;
		int w=rand();
		if(w%3==0){
			password=password+(char)e;
			}
		else if(w%3==2)
			password=password+(char)f;
		else
			password=password+(char)q;
		
	
	}
	cout<<password<<endl;
	return password;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Generate a random password
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Decryption
string decrypt(string input){
	int key=7;
	{//cout<<"Enter the key\n";
		//scanf("%d",&key);
		// if((key<0 || key%26==0)){
		// 	cout<<"Wrong key value!\n";
		// 	return 1;
		// }
	
		// string input;
		// cout<<"Enter the cipher text\n";
		
		//cin.ignore();
		//getline(cin,input);
		//cout<<input<<endl;
		//int len=sizeof(input)/sizeof(char);
	}
	int len=input.length();
	{//int len=6;
	
		//key=key%26;
	}
	for(int i=0;i<len;i++){

		int temp=(int)input[i];
		if((temp>64 && temp<=90)  ){
			temp-=key;
			if(temp<65){
				temp=91-(65-temp);
			}
			
		}
		if((temp>96 && temp<=122)){
			temp-=key;
			if(temp<97){
				temp=123-(97-temp);
			}

		}
		input[i]=(char)temp;
	}
		//cout<<input<<endl;
	//free (input);
	//cout<<"voila\n";
		
	return input;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Encryption
string encrypt(string input){

	int key=7;
	{// cout<<"Enter the key\n";
		// cin>>key;
		// if((key<0 || key%26==0)){
		// 	cout<<"Wrong key value!\n";
		// 	return 1;
		// }
	
		//string input;
		//cout<<"Enter the clear text\n";
		
		//cin.ignore();
		//getline(cin,input);
		//cout<<input<<endl;
		//int len=sizeof(input)/sizeof(char);
	}
	int len=input.length();
	//int len=6;

	//key=key%26;

	for(int i=0;i<len;i++){

		int temp=(int)input[i];
		
		if( (temp>96 && temp<=122)){
			
			temp+=key;
			if(temp>122){
				
				temp=96-(122-temp);
			}
		}

		if((temp>64 && temp<=90)){
			temp+=key;
			if(temp>90){
			temp=64-(90-temp);
			}
		}
		
		input[i]=(char)temp;
	}
	//cout<<input<<endl;
	//free (input);
	//cout<<"voila\n";
	return input;

}

string encrypt2(string input){
	return sha256(input);
}

void addUser(string username,string password){
				ofstream file;
				ofstream file2;
				username=encrypt(username);
				password=encrypt2(password);
				string space=" : ";
				file.open("../data2/file2.txt",ios::app);
				file<<endl<<username+space+password;
				string s="../data2/";
				string a=".txt";
				//file2.open(s+username+a);
				cout<<"Account created!\n\n";
				file.close();
				file2.close();
				return;
}

void validUser(string username){
	cout<<"Login successful\n\n";
	int flag4=1;
	while(flag4){
		cout<<"Press 1 for password list\nPress 2 to add a new password\nPress 0 to logout\n\n";
		int choice2 ;

		cin>>choice2;
		
			switch(choice2){
				case 1 : {
					fstream file;
					string a="../data2/";
					string s=".txt";
					string str=a+username+s;
					file.open(str);
					while(file){
						//cin.ignore();
						string t;
						getline(file,t);
						cout<<decrypt(t)<<endl;
					}
					file.close();
					cout<<"----------------------------\n"<<endl;
					break;
				}
				case 2 : {
					char flagg='y';
					while(flagg=='y'){
					fstream file;
					string a="../data2/";
					string s=".txt";
					string str=a+username+s;
					file.open(str,ios::app);
					string website;
					cout<<"Enter the website\n";
					cin>>website;
					string password;
					char choice3;
					cout<<"Generate password? (y/n)";
					cin>>choice3;
					int flag2=1;
					while(flag2){
						switch(choice3){
							case 'y' : {
								password=generatePass();
								flag2=0;
								break;
							}
							case 'n' : {
								cout<<"Enter the password\n";
								cin>>password;
								flag2=0;
								break;
							}
							default : {
								cout<<"Wrong choice\nTry again\n\n";

							}
						}
					}
					
					string fin=encrypt(website+"\t"+password);
					file<<endl<<fin;
					file.close();
					cout<<"Add another? (y/n)\n\n";
					cin>>flagg;

					}
					break;

				}
				case 0 : {flag4=0;
						  break;
						}
			}


	}
	return ;
}

int authenticate(string input){
	ifstream fin;
	//cout<<"hellp!\n\n";
	///cin.ignore();
	fin.open("../data2/file2.txt");
	while(fin){
		string abc;
		//cin.ignore();
		getline(fin,abc);
		if(abc==input)
			return 1;
	}
	fin.close();
	return 0;
}

int main(){
	char flag='y';
	cout<<"This is an open source password manager\n\n\n";
	while(flag=='y'){
		cout<<"Press 1 to login\nPress 2 to add a new user\nPress 0 to exit\n\n";
		int choice1;
		cin>>choice1;
		switch(choice1){
			case 1: {
				cout<<"Enter the username bla\n";
				string username;
				cin>>username;
				username=encrypt(username);
				cout<<"Enter password\n";
				string password;
				cin>>password;
				password=encrypt2(password);
				cout<<"\n";
				string space=" : ";
				string final=username+space+password;
				//cout
				int auth=authenticate(final);
				if(auth==0){
					cout<<"Wrong username/password\nTry again\n\n";
					break;
				}
				if(auth==1){
					validUser(decrypt(username));
				}
				break;
			}

			case 2 : {
				cout<<"Enter the username\n";
				string username;
				cin>>username;
				int flag3=1;
				string password;
				while(flag3){
					cout<<"Enter password\n";
					string password;
					cin>>password;
					string password2;
					cout<<"Enter again\n";
					cin>>password2;
					
						if(password==password2){
							addUser(username,password);
							flag3=0;
						}
						else{
							cout<<"Passwords dont match, try again\n";
		
						}
				}
				
				break;

			}

			case 0 : {
				flag='n';
				break;
			}
			default : {
				cout<<"Wrong input\nPlease try again\n\n";
				break;
			}
		}


	}
}

