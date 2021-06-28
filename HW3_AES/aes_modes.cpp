#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <fstream>
#include "cryptopp/aes.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/algparam.h"
using namespace std;

typedef unsigned char byte;

std::string enc_cfb(std::string plaintext, CryptoPP::byte key[], CryptoPP::AlgorithmParameters params ){

    std::string ciphertext;

    CryptoPP::CFB_Mode< CryptoPP::AES >::Encryption ecfb;
    ecfb.SetKey( key, CryptoPP::AES::DEFAULT_KEYLENGTH , params );
    CryptoPP::StringSource en(plaintext, true, new CryptoPP::StreamTransformationFilter(ecfb, new CryptoPP::StringSink(ciphertext)));
    return ciphertext;
    
}

std::string enc_ecb(std::string plaintext, CryptoPP::byte key[], std::string padding){

    std::string ciphertext;

    CryptoPP::ECB_Mode< CryptoPP::AES >::Encryption eecb;
    eecb.SetKey( key, CryptoPP::AES::DEFAULT_KEYLENGTH );

    if(padding == "zero"){
        CryptoPP::StringSource en(plaintext, true, new CryptoPP::StreamTransformationFilter(eecb, new CryptoPP::StringSink(ciphertext), CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING));
        return ciphertext;
    }else{
        CryptoPP::StringSource en(plaintext, true, new CryptoPP::StreamTransformationFilter(eecb, new CryptoPP::StringSink(ciphertext), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING));
        return ciphertext;
    }
    
}

std::string enc_cbc(std::string plaintext, CryptoPP::byte key[], CryptoPP::byte iv[], std::string padding){

    std::string ciphertext;

    CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption ecbc;
    ecbc.SetKeyWithIV( key, CryptoPP::AES::DEFAULT_KEYLENGTH , iv );

    if(padding == "zero"){
        CryptoPP::StringSource en(plaintext, true, new CryptoPP::StreamTransformationFilter(ecbc, new CryptoPP::StringSink(ciphertext), CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING));
        return ciphertext;
    }else{
        CryptoPP::StringSource en(plaintext, true, new CryptoPP::StreamTransformationFilter(ecbc, new CryptoPP::StringSink(ciphertext), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING));
        return ciphertext;
    }
}

void printHex(std::string ciphertext, ofstream &file){

    for( int i = 0; i < ciphertext.size(); i++ ) {
        file << setfill('0') << setw(2) << hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i]));
    }
    file << endl;
}

int main(int argc, char* argv[]) {

    CryptoPP::byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
    memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

    CryptoPP::SecByteBlock key_(CryptoPP::AES::DEFAULT_KEYLENGTH), iv_(CryptoPP::AES::BLOCKSIZE);
    memset(key_, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv_, 0x00, CryptoPP::AES::BLOCKSIZE);

    CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters(CryptoPP::Name::FeedbackSize(), 4 /*8-bits*/)
                                      (CryptoPP::Name::IV(), CryptoPP::ConstByteArrayParameter(iv_)); 

    // std::string plaintext = "Hello World!";
    std::string plaintext = "AES is the block cipher standard.";
    for (int i=0 ; i<CryptoPP::AES::BLOCKSIZE ; i++) iv[i] = '0'; //0000000000000000
    for (int i=0 ; i<CryptoPP::AES::DEFAULT_KEYLENGTH ; i++){
        if(i >= 10)
            key[i] = ('A' + (i - 10));
        else if(i == 9)
            key[i] = '0';
        else
            key[i] = ('1' + i);
    } 
    for (int i=0 ; i<CryptoPP::AES::BLOCKSIZE ; i++) iv_[i] = '0'; //0000000000000000
    for (int i=0 ; i<CryptoPP::AES::DEFAULT_KEYLENGTH ; i++){
        if(i >= 10)
            key_[i] = ('A' + (i - 10));
        else if(i == 9)
            key_[i] = '0';
        else
            key_[i] = ('1' + i);
    } 
/*
    string ciphertext[4];
    for(int i = 0; i < 4; i++){
        ciphertext[i] = enc_cfb(plaintext, key, params);
    }
*/

    ofstream file;
    file.open("out.txt");

    printHex(enc_cfb(plaintext, key, params), file);
    printHex(enc_cbc(plaintext, key, iv, "zero"), file);
    for (int i=0 ; i<CryptoPP::AES::BLOCKSIZE ; i++) iv[i] = '9';
    printHex(enc_cbc(plaintext, key, iv, "pkcs"), file);
    printHex(enc_ecb(plaintext, key, "pkcs"), file);

    return 0;
}

