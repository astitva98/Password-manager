#include<iostream>
#include<ctime>
#include<string>
#include<fstream>
#include <stdlib.h>
#include "sha256.h"
#include <cstring>
#include <sstream>
#include "structures.h"
#include "aes1.h"
#include "hp.h"

using namespace std;



string generatePass(){
	srand(time(NULL));
	string password="";
	for(int i=0;i<20;i++){
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

string decipher(string input){
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

string cipher(string input){

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
				uint salt=arc4random();
				string salty=to_string(salt);
				username=cipher(username);
				string saltyPassword=password+salty;
				password=encrypt2(saltyPassword);
				string space=" : ";
				file.open("../data3/file2.txt",ios::app);
				file<<endl<<username+space+password;
				string s="../data3/";
				string a=".txt";
				file2.open(s+"seasoning"+a,ios::app);
				file2<<username<<endl<<salt<<endl;
				cout<<"Account created!\n\n";
				file.close();
				file2.close();
				return;
}

void validUser(string username){
	cout<<"\nLogin successful\n\n";
	int flag4=1;
	while(flag4){
		cout<<"\nPress 1 for password list\nPress 2 to add a new password\nPress 3 to search a new password\nPress 0 to logout\n\n";
		int choice2 ;

		cin>>choice2;
		
			switch(choice2){
				case 1 : {
					fstream file;
					cout<<"---------------------------------\n"<<endl;
					string a="../data3/";
					string s=".txt";
					string str=a+username+s;
					file.open(str);
					while(file){
						string t;
						getline(file,t);
						// if(t.size()<2)	continue;
						// cout<<t.size()<<"gr"<<endl;
						dec(t);
					}
					file.close();
					cout<<"---------------------------------\n\n"<<endl;
					break;
				}
				case 2 : {
					char flagg='y';
					while(flagg=='y'){
					fstream file;
					string a="../data3/";
					string s=".txt";
					string str=a+username+s;
					file.open(str,ios::app);
					string website;
					cout<<"\nEnter the website\n";
					cin>>website;
					string password;
					char choice3;
					cout<<"\nGenerate password? (y/n)\n";
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
								cout<<"\nEnter the password\n";
								cin>>password;
								flag2=0;
								break;
							}
							default : {
								cout<<"\nWrong choice\nTry again\n\n";
								cout<<"\nGenerate password? (y/n)\n";
								cin>>choice3;
								break;
							}
						}
					}
					
					string fin=enc(website+" : "+password);
					file<<endl<<fin;
					file.close();
					cout<<"\nAdd another? (y/n)\n";
					cin>>flagg;

					}
					break;

				}
				case 0 : {flag4=0;
							cout<<"Goodbye!\n\n\n\n\n\n\n\n";
						  break;
						}
			}


	}
	return ;
}

int authenticate(string input){
	ifstream fin;

	fin.open("../data3/file2.txt");

	while(fin){
		string abc;

		getline(fin,abc);

		if(abc==input){
			fin.close();
			return 1;
		}
	}
	fin.close();
	return 0;
}

int main(){
	char flag='y';
	cout<<"This is an open source password manager\n\n";
	while(flag=='y'){
		cout<<"\nPress 1 to login\nPress 2 to add a new user\nPress 0 to exit\n\n";
		int choice1;
		cin>>choice1;
		switch(choice1){
			case 1: {
				cout<<"\nEnter the username\n";
				string username;
				cin>>username;

				username=cipher(username);

				cout<<"\nEnter password\n";
				string password;
				cin>>password;

				string space=" : ";
				string salty;

				ifstream file3;
				file3.open("../data3/seasoning.txt");
				cin.ignore();

				while(file3){
					string temp;
					getline(file3,temp);
					if(temp==username){
						getline(file3,salty);
						break;
					}
				}

				cout<<salty<<endl;

				password=encrypt2(password+salty);
				file3.close();

				string final=username+space+password;

				int auth=authenticate(final);
				if(auth==0){
					cout<<"\nWrong username/password\nTry again\n\n";
					break;
				}
				if(auth==1){
					validUser(decipher(username));
				}
				break;
			}

			case 2 : {
				cout<<"\nEnter the username\n";
				string username;
				cin>>username;

				int flag3=1;

				string password;

				while(flag3==1){
					cout<<"\nEnter password (length greater than 16), or press 0 to exit\n";
					string password;
					cin>>password;
					if(password == "0"){
						flag3=-1;
						break;
					}
					if(password.size()<16){
						cout<<"\npassword too short, please try again\n";
						continue;
					}

					string password2;
					cout<<"\nEnter again\n";
					cin>>password2;
					
						if(password==password2 ){
							addUser(username,password);
							flag3=0;
						}
						else{
							cout<<"\nPasswords dont match, try again\n";
		
						}
				}

				
				break;

			}

			case 0 : {
				flag='n';
				break;
			}
			default : {
				cout<<"\nWrong input\nPlease try again\n\n";
				break;
			}
		}


	}
}

