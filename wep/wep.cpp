#include<bits/stdc++.h>

using namespace std;

string num_to_string(unsigned int val){
	string ans = "";
	while(val != 0){
		int x = val%10;
		char y = x + '0';
		ans  = y + ans;
		val /= 10;
	}
	return ans;
}

string rc4(string plaintext, string key){
	int S[256];
	for(int i = 0; i < 256; i++)
		S[i] = i;
	int j = 0;
	int keylength = 8;
	for(int i = 0; i < 256; i++){
		j = (j + S[i] + key[i%keylength])%256;
		S[i] += S[j];
		S[j] = S[i] - S[j];
		S[i] -= S[j];
	}
	
	int i = 0;
	j = 0;
	int length = plaintext.length();
	string ciphertext = "";
	for(int k = 0; k < length; k++){
		i = (i + 1)%256;
		j = (j + S[i])%256;
		S[i] += S[j];
		S[j] = S[i] - S[j];
		S[i] -= S[j];
		int rnd = S[(S[i] + S[j])%256];
		char x = rnd^plaintext[k];
		ciphertext += x;
	}
return ciphertext;
}

string crc32fun(string text){
     unsigned int i, j;
     unsigned int c;
     int table[256];
     for (i = 0; i < 256; i++)
       {
	 for (c = i << 24, j = 8; j > 0; --j)
	   c = c & 0x80000000 ? (c << 1) ^ 0x04c11db7 : (c << 1);
	 table[i] = c;
       }
     unsigned int crc32 = 0xFFFFFFFF;
     unsigned int index;
     int length = text.length();
     for(int k = 0; k < length; k++){
	index = (crc32^text[k])&(0xFF);
	crc32 = (crc32<<8)^table[index];
     }
     crc32 = crc32^0xFFFFFFFF;
return num_to_string(crc32);
}		


int main(){
	cout << "Enter plain text that has to be encrypted" << endl;
	string plaintext;
	getline(cin, plaintext);
	cout << "Enter 24 bit initialization vector ie 3 ascii characters" << endl;
	string iv;
	cin >> iv;
	cout << "Enter 40 bit key ie 5 ascii characters" << endl;
	string key;
	cin >> key;
	string key64bit = iv + key;


	string crc32 = crc32fun(plaintext);
	string text = plaintext + crc32;
	string ciphertext = rc4(text, key64bit);
	string wepoutput = iv + ciphertext;

	cout << endl << endl << "Encrypted WEP output ----------" << endl;
	cout << "ASCII Value:" << endl;
	int length = wepoutput.length();
	for(int i = 0; i < length; i++){
		if((i%15 == 0) && i != 0) cout << endl;
		cout << +(u_int8_t)wepoutput[i] << " ";}
	
	cout << endl << "ASCII Print:" << endl;
	cout << wepoutput << endl << endl;


	cout << "Decrypted WEP output-----------" << endl;
	string ciphermess = wepoutput.substr(3);
	string message = rc4(ciphermess, key64bit);
	cout << message << endl;
	string actual_message = message.substr(0, plaintext.length());
	string ICV = message.substr(plaintext.length());
	cout << "ICV = " << ICV << endl;
	string calculated_ICV = crc32fun(actual_message);
	cout << "Calculated_ICV = " << calculated_ICV << endl;
	if(ICV == calculated_ICV){
		 cout << "Value Matched" << endl;
		 cout << "Message = " << actual_message << endl;
	}
	else cout << "Value Unmatched" << endl;
return 0;
}