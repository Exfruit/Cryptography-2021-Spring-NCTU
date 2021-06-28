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
#include "cryptopp/rsa.h"
#include "cryptopp/osrng.h"
using namespace std;
using namespace CryptoPP;

void Encryption_Use_PublicKey(string message, Integer n, Integer e, ofstream &file){
	RSA::PublicKey pubKey;
	pubKey.Initialize(n, e);

	Integer m((const byte *)message.data(), message.size());
	// cout << "m : " << m << '\n';

	Integer c = pubKey.ApplyFunction(m);
	file << hex << c << endl;
}
void Decryption_Use_PrivateKey(Integer d, Integer n, Integer c, Integer e, ofstream &file){
	RSA::PrivateKey privKey;
	privKey.Initialize(n, e, d);

	AutoSeededRandomPool prng;
	string recovered;
	Integer r = privKey.CalculateInverse(prng, c);
	// cout << "r: " << hex << r << endl;

	size_t req = r.MinEncodedSize();
	recovered.resize(req);

	r.Encode((byte *) &recovered[0], recovered.size());
	file << recovered << endl;
	file << hex << e << endl;
}

int main(int argc, char const *argv[])
{
	////////////////////////////////////////////////
	// Generate keys
	// AutoSeededRandomPool prng;
/*
	InvertibleRSAFunction params;
	params.Initialize(rng, 512);
	////////////////////////////////////////////////
*/
	Integer n1("0xb14022eef719f1bb"), e1("0x11"),
				n2("0xb2c8d1404ed5fc2f7ad1254bb428f0d5"), e2("0x11"), 
					n3("0xcf625a8e47bc1cf9a3b517b31d870108c0cd97466003842a3b394d6cd857e9b7"), e3("0x10001");
	Integer _c1("0x154c638cd3615216"), _d1("0x16282b21a7866bf5"), _n1("0x9d001e6473dfacf9"), _e1("0x10001"),
				_c2("0xa1676afd68a2fc67dac32c633600b76fa90aca9f9cca5201490a20c8b01a061a"),
					_d2("0x12e6a85100b889c9905a939b274a91bc57ca85d52e6c464fb455c86a29d63c89"),
						_n2("0xd6361e40b2d619970ead338912a273adb75a4ce21356304834753fe94e6de24b"),
							_e2("0x11");

/*	
	RSA::PrivateKey privKey;
	privKey.Initialize(n, e, d);
*/
	
/*
	RSA::PrivateKey privateKey(params);
	RSA::PublicKey publicKey(params);
*/
	ofstream file;
    file.open("out.txt");
	
	// Encryption_Use_PublicKey("Alice", n1, e1, file);
	Encryption_Use_PublicKey("Hello World!", n2, e2, file);
	Encryption_Use_PublicKey("RSA is public key.", n3, e3, file);

	// Decryption_Use_PrivateKey(_d1, _n1, _c1, _e1, file);
	Decryption_Use_PrivateKey(_d2, _n2, _c2, _e2, file);
	
	// Decryption_Use_PrivateKey(d, n, c, e);

/*
	////////////////////////////////////////////////
	// Encryption
	RSAES_OAEP_SHA_Encryptor e(publicKey);

	StringSource ss1(plain, true,
	    new PK_EncryptorFilter(rng, e,
	        new StringSink(cipher)
	   ) // PK_EncryptorFilter
	); // StringSource
	StringSource ss( cipher, true,
    	new HexEncoder(
       	 	new StringSink( encoded )
    	) // HexEncoder
	); // StringSource
	cout << encoded << '\n';
	////////////////////////////////////////////////
	// Decryption
	RSAES_OAEP_SHA_Decryptor d(privateKey);

	StringSource ss2(cipher, true,
	    new PK_DecryptorFilter(rng, d,
	        new StringSink(recovered)
	   ) // PK_DecryptorFilter
	); // StringSource
	cout << recovered << '\n';
	// cout << "Recovered plain text" << endl;
*/


	return 0;


}	