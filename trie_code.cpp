#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#define alpha_size 36
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
using namespace std;
string word;

struct TrieNode {
    bool EndOfWord;
    vector<int> documents;
    TrieNode *children[alpha_size];
    int freq;
};

// Create and Return a New Trie Node.
struct TrieNode *createNode() {
    TrieNode *pNode = new TrieNode;
    pNode->EndOfWord = false;

    for (int t = 0; t < alpha_size; t++) {
        pNode->children[t] = nullptr;
    }
    return pNode;
}



class Trie{
	public:
		TrieNode *root = createNode();
		
	Trie(){
	}
	
	void insert_doc(string page, int doc){
	int init, end;
	int letter = 0;
	while (letter < page.length()) {
		while (page[letter] == ' ' && letter < page.length()) letter++;
		init = letter;
		while (page[letter] != ' ' && letter < page.length()) letter++;
		end = letter - 1;
		if (init <= end){
			string word = page.substr(init, end - init + 1);
			cout << "insertando a palavra :%"+ word +"%" << endl;
			insert_word(word, doc);
			}
		}
	}
		
	
	
	// Insert a word into a Trie.
	void insert_word(string key, int doc) {
	    TrieNode *crawl = root;
	
	    for (int t = 0; t < key.length(); t++) {
	        int index = key[t] - 'a';
	
	        if (!crawl->children[index]) {
	            crawl->children[index] = createNode();
	        }
	
	        crawl = crawl->children[index];
	        // crawl->freq++; Uncomment for Count of every node hit count.
	    }
	    crawl->freq++;  // For the count of word hit count.
	    crawl->EndOfWord = true;
	    if (find(crawl->documents.begin(), crawl->documents.end(), doc) != crawl->documents.end()){
		}
		else{
			crawl->documents.push_back(doc);
		}
	}
	
	// Search for a word in the Dictionary.
	bool search_word(string key) {
	    TrieNode *crawl = root;
	
	    for (int t = 0; t < key.length(); t++) {
	        int index = key[t] - 'a';
	
	        if (!crawl->children[index])
	            return false;
	
	        crawl = crawl->children[index];
	    }
	    return (crawl != nullptr && crawl->EndOfWord);
	}
	
	TrieNode* search_word_node(string key){
		TrieNode *crawl = root;
		TrieNode *null = root;
	    for (int t = 0; t < key.length(); t++) {
	        int index = key[t] - 'a';
	        
	        if (!crawl->children[index])
	            return null;
	        
	        crawl = crawl->children[index];
	    }
	    if (crawl != nullptr && crawl->EndOfWord){
	    	return crawl;
	    }
	    else{
	    	return null;
		}
	}
	
	
	
	
	bool isLastNode(TrieNode *root) {
	    for (int t = 0; t < alpha_size; t++) {
	        if (root->children[t])
	            return false;
	    }
	    return true;
	}
	
	
	
	void printDictionary() {
	    if (root->EndOfWord)
	        cout << word << endl;
	
	    if (isLastNode(root))
	        return;
	
	    for (int t = 0; t < alpha_size; t++) {
	        if (root->children[t]) {
	            word.push_back(97 + t);
	            printDictionary(root->children[t]);
	            word.pop_back();
	        }
	    }
	    return;
	}
	void printDictionary(TrieNode *root) {
	    if (root->EndOfWord)
	        cout << word << endl;
	
	    if (isLastNode(root))
	        return;
	
	    for (int t = 0; t < alpha_size; t++) {
	        if (root->children[t]) {
	            word.push_back(97 + t);
	            printDictionary(root->children[t]);
	            word.pop_back();
	        }
	    }
	    return;
	}
			
};

void print(std::vector <int> const &a) {
   
   for(int i=0; i < a.size(); i++)
      std::cout << a.at(i) << endl;
}

char to_lowercase(char c){
	if ( c>= 'A' && c <= 'Z')
		return c+32;
	return c;
}

int main(){

	return 9;
}

