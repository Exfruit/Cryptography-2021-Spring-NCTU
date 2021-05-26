#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "cryptopp/aes.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/algparam.h"
#include "cryptopp/rsa.h"
#include "cryptopp/osrng.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/files.h"
using namespace std;
using namespace CryptoPP;

string question(string source){
	string value;
	SHA256 hash;

	StringSource ss(source, true,
		new HashFilter(hash, 
			new HexEncoder( 
				new StringSink(value))));

	// cout << source << endl;
	// file << value << endl;
	return value;
}
string hex_string(string source){
	string value, hexmsg;
	SHA256 hash;
	StringSource ss1(source, true, new HexDecoder(new StringSink(hexmsg)));

	StringSource ss(hexmsg, true,
		new HashFilter(hash, 
			new HexEncoder( 
				new StringSink(value))));

	// cout << source << endl;
	// file << value << endl;
	return value;
}


int main(int argc, char const *argv[])
{
	ofstream file;
	file.open("out.txt");

	file << question("Bitcoin is a cryptocurrency, a form of electronic cash.") << endl;

	int NONCE_int = 0;
	string source = question("Bitcoin");
	bool toBreak = false;
	string Preimage, HashValue;

	file << "0" << endl;
	file << source << endl;
	file << "00000000" << endl;
	file << hex_string(source + "00000000") << endl;
	// cout << "Found 0!" << endl;
	source = hex_string(source + "00000000");

	for(int i = 1; i < 64; i++){
		toBreak = false;
		for(long long j = NONCE_int; j <= 4294967295; j++){
			
			// cout << j << " " ;

			//deal with nonce
			stringstream sstream;
			sstream << uppercase << std::hex << j;
			string nonce = sstream.str();
			if(nonce.size() == 1){
				nonce = "0000000" + nonce;
			}
			else if (nonce.size() == 2){
				nonce = "000000" + nonce;
			}
			else if (nonce.size() == 3){
				nonce = "00000" + nonce;
			}
			else if (nonce.size() == 4){
				nonce = "0000" + nonce;
			}
			else if (nonce.size() == 5){
				nonce = "000" + nonce;
			}
			else if (nonce.size() == 6){
				nonce = "00" + nonce;
			}
			else if (nonce.size() == 7){
				nonce = "0" + nonce;
			}

			//generate the hashvalue
			Preimage = source + nonce;
			HashValue = hex_string(Preimage);
			/*if(i == 0){
				toBreak = true;
				file << i << endl;
				file << source << endl;
				file << nonce << endl;
				file << HashValue << endl;
				source = HashValue;
				break;
			}*/
			if(1){
				for(int k = 0; k <= i - 1; k++){
					if(HashValue[k] != '0')
						break;
					else if(i - 1 == k && HashValue[i] != '0'){
						// cout << "fuck" << endl;
						toBreak = true;
						file << i << endl;
						file << source << endl;
						file << nonce << endl;
						file << HashValue << endl;
						source = HashValue;
						NONCE_int = j;
						// cout << "Found " << i << "!" << endl;
					}
				}
			}
			if(j % 1000000 == 0){
				// cout << "Now is at nonce = " << j << " ..." << endl;
			}
			if(j == 4294967295){
				// cout << "Not found any shit at # of leading zero = " << i << ", Fuck." << endl;
				return 0;
			}
			if(toBreak == true){
				break;
			}
		}
	}
	
	
	// cout << result << endl;		
	
	return 0;
}






















