#ifndef ENC
#define ENC
#include<cstring>

#include "structures.h"
#include"aes1.h"
using namespace std;
string enc(string message1 ){

	char* message = new char[message1.size()+1];
	message[message1.size()] = '\0';
	for(int i=0;i<message1.size();i++){
		message[i] = message1[i];
	}
	// Pad message to 16 bytes
	int originalLen = strlen((const char *)message);

	int paddedMessageLen = originalLen;

	if ((paddedMessageLen % 16) != 0) {
		paddedMessageLen = (paddedMessageLen / 16 + 1) * 16;
	}

	unsigned char * paddedMessage = new unsigned char[paddedMessageLen];
	for (int i = 0; i < paddedMessageLen; i++) {
		if (i >= originalLen) {
			paddedMessage[i] = 0;
		}
		else {
			paddedMessage[i] = message[i];
		}
	}

	unsigned char * encryptedMessage = new unsigned char[paddedMessageLen];

	string str  = "01 04 02 03 01 03 04 0A 09 0B 07 0F 0F 06 03 00";
	
	istringstream hex_chars_stream(str);
	unsigned char key[16];
	int i = 0;
	unsigned int c;
	while (hex_chars_stream >> hex >> c)
	{
		key[i] = c;
		i++;
	}

	unsigned char expandedKey[176];

	KeyExpansion(key, expandedKey);

	for (int i = 0; i < paddedMessageLen; i += 16) {
		AESEncrypt(paddedMessage+i, expandedKey, encryptedMessage+i);
	}
	string ans ="";
	for(int i=0;i<paddedMessageLen;i++){
		ans.push_back((char)encryptedMessage[i]);
	}
	delete[] paddedMessage;
	delete[] encryptedMessage;
	delete[] message;

	return ans;

}


void dec(string msgstr){
	char * msg = new char[msgstr.size()+1];

	strcpy(msg, msgstr.c_str());

	int n = strlen((const char*)msg);

	unsigned char * encryptedMessage = new unsigned char[n];
	for (int i = 0; i < n; i++) {
		encryptedMessage[i] = (unsigned char)msg[i];
	}

	// Free memory
	delete[] msg;

	string keystr = "01 04 02 03 01 03 04 0A 09 0B 07 0F 0F 06 03 00";
	

	istringstream hex_chars_stream(keystr);
	unsigned char key[16];
	int i = 0;
	unsigned int c;
	while (hex_chars_stream >> hex >> c)
	{
		key[i] = c;
		i++;
	}

	unsigned char expandedKey[176];

	KeyExpansion(key, expandedKey);
	
	int messageLen = strlen((const char *)encryptedMessage);

	unsigned char * decryptedMessage = new unsigned char[messageLen];

	for (int i = 0; i < messageLen; i += 16) {
		AESDecrypt(encryptedMessage + i, expandedKey, decryptedMessage + i);
	}

	string ret="";

	for(int i=0;i<(messageLen);i++){
		cout<<(char)decryptedMessage[i];
	}
	cout<<endl;

	// return ret;s
}

#endif