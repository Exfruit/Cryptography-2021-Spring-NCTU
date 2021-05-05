/*input
sendmoremoney
3 11 5 7 17 21 0 11 14 8 7 13 9
cashnotneeded
*/
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
	string text;
	getline(cin, text);
	int key[text.size()];
	for(int i = 0; i < text.size(); i++){
		cin >> key[i];
	}
	for(int i = 0; i < text.size(); i++){
		text[i] = (text[i] - 97 + key[i]) % 26 + 97;
	}
	cout << text << '\n';
	cin.ignore(1, '\n');
	string fake_text;
	getline(cin, fake_text);
	cout << fake_text << '\n';
	int new_key[text.size()];
	for(int i = 0; i < text.size(); i++){
		new_key[i] = (text[i] - fake_text[i] + 26) % 26;
	}
	for(int i = 0; i < text.size() - 1; i++){
		cout << new_key[i] << ' ';
	}
	cout << new_key[text.size() - 1] << '\n';
	return 0;
}