/*input
cryptographic
*/
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
	int key[3] = {'e' - 97, 'n' - 97, 'g' - 97};
	// cout << key[0] << '\n' << key[1] << '\n' << key[2];
	string text;
	getline(cin, text);
	int t = 0;
	for(int i = 0; i < text.size(); i++){
		text[i] = (text[i] - 97 + key[t++]) % 26 + 97;
		if(t == 3)
			t = 0;
	}
	cout << text;
	return 0;
}