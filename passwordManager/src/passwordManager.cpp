#include<iostream>
#include<ctime>
#include<string>
#include<fstream>
using namespace std;

//add a add user function, which also creates a file in ../data/ directory
//change encryption method
//learn how to store passwords 



string generatePass(){
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

void addUser(string username,string password){
				ofstream file;
				username=encrypt(username);
				password=encrypt(password);
				file.open("../data/file.txt",ios::app);
				file<<endl<<username+password;
				cout<<"Account created!\n\n";
				file.close();
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
					string a="../data/";
					string s=".txt";
					string str=a+username+s;
					file.open(str);
					while(file){
						//cin.ignore();
						string t;
						getline(file,t);
						cout<<t<<endl;
					}
					file.close();
					cout<<"----------------------------\n"<<endl;
					break;
				}
				case 2 : {
					char flagg='y';
					while(flagg=='y'){
					fstream file;
					string a="../data/";
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
							}
							default : {
								cout<<"Wrong choice\nTry again\n\n";

							}
						}
					}
					
					string fin=website+"\t"+password;
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
	cout<<"hellp!\n\n";
	///cin.ignore();
	fin.open("../data/file.txt");
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
				password=encrypt(password);
				cout<<"\n";
				string final=username+password;
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

