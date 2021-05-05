/*input
meet me at the usual place at ten rather than eight o clock
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
	int key[4] = {7, 3, 2, 5};
	string text;
	getline(cin, text);
	int text_length = text.size();
	for(int i = 0; i < text_length; i++){
		if(text[i] == ' '){
			text_length--;
			for(int j = i; j < text_length; j++){
				text[j] = text[j + 1];
			}
		}
	}
	text[text_length] = 'q';
	text.resize(text_length + 1);
	// cout << text << '\n';
	for(int i = 0; i < text.size(); i += 2){
		int temp = text[i];
		text[i] = ((text[i] - 97) * key[0] + ((text[i + 1] - 97) * key[2])) % 26 + 97;
		text[i + 1] = ((temp - 97) * key[1] + ((text[i + 1] - 97) * key[3])) % 26 + 97;
		
	}
	cout << text;
}