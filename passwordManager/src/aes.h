
#ifndef AES_H
#define AES_H


void AddRoundKey(unsigned char * , unsigned char * );


void SubBytes(unsigned char * ) ;

void ShiftRows(unsigned char * ) ;

void MixColumns(unsigned char * );

void Round(unsigned char * , unsigned char * ) ;

void FinalRound(unsigned char * , unsigned char * ) ;

void AESEncrypt(unsigned char * , unsigned char * , unsigned char * ) ;

void SubRoundKey(unsigned char * , unsigned char * ) ;


void InverseMixColumns(unsigned char * ) ;

void ShiftRows1(unsigned char * ) ;


void SubBytes1(unsigned char * ) ;


void Round1(unsigned char * , unsigned char * ) ;

void InitialRound(unsigned char * , unsigned char * ) ;


void AESDecrypt(unsigned char * , unsigned char * , unsigned char * ) ;
#endif