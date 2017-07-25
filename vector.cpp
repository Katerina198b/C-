#include <iostream>
#include <string>
#include <iterator>
#include <ctype.h>
#include <vector>
#include <bits/stdc++.h>
#include <map>
#include <string> //для strlen()
#include <locale>
using namespace std;
#define MAX_WORD_LENGTH 15

void reverse_word(string& word) {
	reverse(word.begin(), word.end()); 
}

void print_words(string word) {
	
	cout << word << ' ';
	reverse(word.begin(), word.end());
	cout << word << endl;
}


int main() {
	int n;
	cin >> n;
	string word;
	string str_words[n];
	vector<string> words_vector;
	map <int,vector <string>> words;
	map <int,vector <string>>::iterator it;

	for (int i = 0; i < n ; i++) {
		cin >> word;
		words[word.length()].push_back(word);
	}
	
	for (int i =0; i <= MAX_WORD_LENGTH; i++) {
		if ((it = words.find(i)) != words.end()) {
			cout << i << endl;
			words_vector = it->second;
			for_each(words_vector.begin(), words_vector.end(), reverse_word);
			sort(words_vector.begin(), words_vector.end());
			//reverse(words_vector.begin(), words_vector.end());
			for_each(words_vector.begin(), words_vector.end(), print_words);
		}	
	}	
	return 0;
}
