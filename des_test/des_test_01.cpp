/*input
64664
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <time.h>
using namespace std;
 
bitset<64> key;                
bitset<48> subKey[16];
//initial permutation 
int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
			60, 52, 44, 36, 28, 20, 12, 4,
			62, 54, 46, 38, 30, 22, 14, 6,
			64, 56, 48, 40, 32, 24, 16, 8,
			57, 49, 41, 33, 25, 17, 9,  1,
			59, 51, 43, 35, 27, 19, 11, 3,
			61, 53, 45, 37, 29, 21, 13, 5,
			63, 55, 47, 39, 31, 23, 15, 7};
 
int IP_1[] = {40, 8, 48, 16, 56, 24, 64, 32,
			  39, 7, 47, 15, 55, 23, 63, 31,
			  38, 6, 46, 14, 54, 22, 62, 30,
			  37, 5, 45, 13, 53, 21, 61, 29,
			  36, 4, 44, 12, 52, 20, 60, 28,
			  35, 3, 43, 11, 51, 19, 59, 27,
			  34, 2, 42, 10, 50, 18, 58, 26,
			  33, 1, 41,  9, 49, 17, 57, 25};
//permutaion/contraction
int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
			   1, 58, 50, 42, 34, 26, 18,
			  10,  2, 59, 51, 43, 35, 27,
			  19, 11,  3, 60, 52, 44, 36,
			  63, 55, 47, 39, 31, 23, 15,
			   7, 62, 54, 46, 38, 30, 22,
			  14,  6, 61, 53, 45, 37, 29,
			  21, 13,  5, 28, 20, 12,  4}; 

int PC_2[] = {14, 17, 11, 24,  1,  5,
			   3, 28, 15,  6, 21, 10,
			  23, 19, 12,  4, 26,  8,
			  16,  7, 27, 20, 13,  2,
			  41, 52, 31, 37, 47, 55,
			  30, 40, 51, 45, 33, 48,
			  44, 49, 39, 56, 34, 53,
			  46, 42, 50, 36, 29, 32};
//shift times 
int shiftBits[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
 //expansion 
int E[] = {32,  1,  2,  3,  4,  5,
		    4,  5,  6,  7,  8,  9,
		    8,  9, 10, 11, 12, 13,
		   12, 13, 14, 15, 16, 17,
		   16, 17, 18, 19, 20, 21,
		   20, 21, 22, 23, 24, 25,
		   24, 25, 26, 27, 28, 29,
		   28, 29, 30, 31, 32,  1};

int S_BOX[8][4][16] = {
	{  
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},  
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},  
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, 
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} 
	},
	{  
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},  
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, 
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},  
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}  
	}, 
	{  
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},  
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},  
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},  
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}  
	}, 
	{  
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},  
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},  
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},  
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}  
	},
	{  
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},  
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},  
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},  
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}  
	},
	{  
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},  
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},  
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},  
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}  
	}, 
	{  
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},  
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},  
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},  
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}  
	}, 
	{  
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},  
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},  
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},  
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}  
	} 
};
//permutation
int P[] = {16,  7, 20, 21,
		   29, 12, 28, 17,
		    1, 15, 23, 26,
		    5, 18, 31, 10,
		    2,  8, 24, 14,
		   32, 27,  3,  9,
		   19, 13, 30,  6,
		   22, 11,  4, 25 };

bitset<32> F(bitset<32> R, bitset<48> K){
	bitset<48> expansion32_48;
	for(int i = 0; i < 48; i++){
		expansion32_48[47 - i] = R[32 - E[i]];
	}
	// cout << expansion32_48 << '\n';
	bitset<48> XORout = expansion32_48 ^ K;
	bitset<32> Sout;
	for(int i = 0, j = 0; i < 48; i += 6, j += 4){
		int row = XORout[47 - i] * 2 + XORout[47 - i - 5];//0 = 00, 1 = 01, 2 = 10, 3 = 11
		int col = XORout[47 - i - 1] * 8 + XORout[47 - i - 2] * 4 + XORout[47 - i - 3] * 2 + XORout[47 - i - 4];
		int value = S_BOX[i / 6][row][col];
		bitset<4> temp(value);
		Sout[31 - j] = temp[3];
		Sout[31 - j - 1] = temp[2];
		Sout[31 - j - 2] = temp[1];
		Sout[31 - j - 3] = temp[0];
	}
	// cout << Sout << '\n';
	bitset<32> temp = Sout;
	for(int i = 0; i < 32; i++){
		Sout[31 - i] = temp[32 - P[i]];
	}
	return Sout;
}
bitset<64> encrypt(bitset<64> plaintext){
	bitset<32> left;
	bitset<32> right;
	bitset<64> IPout;
	for(int i = 0; i < 64; i++){
		IPout[63 - i] = plaintext[64 - IP[i]];
	}
	// cout << IPout << '\n';
	for(int i = 32; i < 64; i++){
		left[i - 32] = IPout[i];
	}
	for(int i = 0; i < 32; i++){
		right[i] = IPout[i];
	}
	// cout << right << '\n';
	bitset<32> temp;
	for(int i = 0; i < 16; i++){
		temp = right;
		right = left ^ F(right, subKey[i]);
		left = temp;
		// cout << right << '\n';
		// cout << left << '\n';
	}
	bitset<64> cipher;
	for(int i = 0; i < 32; i++){
		cipher[i] = left[i];
	}
	for(int i = 32; i < 64; i++){
		cipher[i] = right[i - 32];
	}
	// cout << cipher << '\n';
	bitset<64> IP_1out;
	for(int i = 0; i < 64; i++){
		IP_1out[63 - i] = cipher[64 - IP_1[i]];
	}
	// cout << IP_1out << '\n';
	return IP_1out;
}
void generateKeys(){
	bitset<56> PC_1Key;
	bitset<28> left;
	bitset<28> right;
	bitset<48> PC_2Key;
	for(int i = 0; i < 56; i++){
		PC_1Key[55 - i] = key[64 - PC_1[i]];
	}
	// cout << PC_1Key << '\n';
	
	for(int j = 28; j < 56; j++){
		left[j - 28] = PC_1Key[j];
	}
	for(int j = 0; j < 28; j++){
		right[j] = PC_1Key[j];
	}

	for(int i = 0; i < 16; i++){
		// cout << "left : " << left << '\n';
		// cout << "right : " << right << '\n';
		bitset<28> temp = left;
		for(int j = 27; j >= 0; j--){
			if(j - shiftBits[i] < 0)
				left[j] = temp[j + 28 - shiftBits[i]];
			else
				left[j] = temp[j - shiftBits[i]];
		}
		// cout << left << '\n';
		temp = right;
		for(int j = 27; j >= 0; j--){
			if(j - shiftBits[i] < 0)
				right[j] = temp[j - shiftBits[i] + 28];
			else
				right[j] = temp[j - shiftBits[i]];
		}
		for(int j = 28; j < 56; j++){
			PC_1Key[j] = left[j - 28];
		}
		for(int j = 0; j < 28; j++){
			PC_1Key[j] = right[j];
		}
		for(int j = 0; j < 48; j++){
			PC_2Key[47 - j] = PC_1Key[56 - PC_2[j]];
		}
		subKey[i] = PC_2Key;
		// cout << "subKey : "<< subKey[i] << '\n';
	}
}
bitset<64> char_Bitset(char input[8])
{
	bitset<64> bits;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			bits[56 - i * 8 + j] = ((input[i] >> j) & 1);
		}
	}
	// cout << bits << '\n';
	return bits;
}
int main(int argc, char const *argv[])
{
	char input[20];
	char k[8], plain[8] = {'s', 'e', 'c', 'u', 'r', 'i', 't', 'y'};
	char test_cipher[16] = {'D', '2', 'C', 'C', '6', 'D', '9', '8', '9', '3', '9', 'C', '0', 'E', '0', '1'};
	bitset<64> plain_bit;
	ifstream file1;
	ofstream file2;
	file1.open("DES-Key-Plaintext.txt");
	file2.open("out.txt");
	// int j = 0;
	/*
	clock_t start, end;
	double cpu_time_used[1000], total_time[5];
	int x = 0;
	do{
		file1.getline(input, 20);
		// for(int i = 0; i < 20; i++){
		// 	cout << input;
		// }
		// cout << '\n';
		for(int i = 0; i < 8; i++){
			k[i] = input[i];
			plain[i] = input[i + 9];
			// cout << k[i];
			// cout << plain[i];
		}
		char ans[16];
		for(int y = 0; y < 1000; y++){
			start = clock();
			plain_bit = char_Bitset(plain);
			key = char_Bitset(k);
			// cout << "ya" << '\n';
			generateKeys();
			bitset<64> cipher = encrypt(plain_bit);
			// j++;
			// if(j == 10)
			// 	break;
			int temp;
			// cout << cipher << '\n';
			for(int i = 0, j = 0; i < 64; i += 4, j++){
				temp = 8 * cipher[63 - i] + 4 * cipher[63 - i - 1] + 2 * cipher[63 - i - 2] + cipher[63 - i - 3];
				// cout << temp << " ";
				if(temp < 10)
					ans[j] = temp + 48;
				else
					ans[j] = temp - 10 + 65;
			}
			// cout << '\n';
			//file2 << ans;
			end = clock();
			cpu_time_used[y] = ((double) (end - start)) / CLOCKS_PER_SEC;
			// cout << cpu_time_used[y] << '\n';
		}

		for(int i = 0; i < 16; i++){
			file2 << ans[i];
		}
		file2 << '\n';

		for(int y = 0; y < 1000; y++){
			total_time[x] += cpu_time_used[y];
		}
		// cout << total_time[x] << '\n';
		total_time[x] /= 1000;	
		// cout << total_time[x] << '\n';
		x++;
	} while(!file1.eof());
	*/
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	char ans[16];
	for(int a1 = 0; a1 < 10; a1++){
		for(int a2 = 0; a2 < 10; a2++){
			for(int a3 = 0; a3 < 10; a3++){
				for(int a4 = 0; a4 < 10; a4++){
					for(int a5 = 0; a5 < 10; a5++){
						k[0] = '0';
						k[1] = '0';
						k[2] = '0';
						k[3] = 48 + a1;
						k[4] = 48 + a2; 
						k[5] = 48 + a3;
						k[6] = 48 + a4;
						k[7] = 48 + a5;
						plain_bit = char_Bitset(plain);
						key = char_Bitset(k);
						generateKeys();
						bitset<64> cipher = encrypt(plain_bit);
						int temp;
						// cout << cipher << '\n';
						for(int i = 0, j = 0; i < 64; i += 4, j++){
							temp = 8 * cipher[63 - i] + 4 * cipher[63 - i - 1] + 2 * cipher[63 - i - 2] + cipher[63 - i - 3];
							// cout << temp << " ";
							if(temp < 10)
								ans[j] = temp + 48;
							else
								ans[j] = temp - 10 + 65;
							if(ans[j] != test_cipher[j]){
								break;
							}
							if(j == 15){
								for(int x = 0; x < 8; x++){
									cout << k[x];
								}
								cout << '\n';
								end = clock();
								cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
								cout << cpu_time_used << '\n'; 
								return 0;
							}
						}
					}
				}
			}
		}
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	cout << cpu_time_used << '\n'; 
	// for(int i = 0; i < 5; i++){
	// 	cout << total_time[i] << '\n';
	// }
	/*
	double used_time = 0;
	for(int i = 0; i < 5; i++){
		used_time += total_time[i];
	}
	// cout << used_time << '\n';
	used_time /= 5;
	file2 << used_time << '\n';
*/	return 0;
}