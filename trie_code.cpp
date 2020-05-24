#include <iostream>
#include <vector>
#include <string>
#define alpha_size 26
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
TrieNode *createNode() {
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
		if (init <= end) insert_word(page.substr(init, end - init + 1), doc);
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
	    crawl->documents.push_back(doc);
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
	
	bool isLastNode(TrieNode *root) {
	    for (int t = 0; t < alpha_size; t++) {
	        if (root->children[t])
	            return false;
	    }
	    return true;
	}
	
	void suggestWords(string prefix, TrieNode *root) {
	    if (root->EndOfWord == true)
	        cout << prefix << endl;
	
	    if (isLastNode(root)) {
	        return;
	    }
	
	    for (int t = 0; t < alpha_size; t++) {
	        if (root->children[t]) {
	            prefix.push_back(97 + t);
	            suggestWords(prefix, root->children[t]);
	            prefix.pop_back();
	        }
	    }
	    return;
	}
	
	int autoSuggest(const string query) {
	    TrieNode *crawl = root;
	    int level;
	    int n = query.length();
	
	    for (level = 0; level < n; level++) {
	        int ind = CHAR_TO_INDEX(query[level]);
	
	        if (!crawl->children[ind])
	            return 0;
	
	        crawl = crawl->children[ind];
	    }
	
	    bool isWord = (crawl->EndOfWord == true);
	    bool isLast = isLastNode(crawl);
	
	    if (isWord && isLast) {
	        cout << query << endl;
	        return -1;
	    }
	
	    if (!isLast) {
	        string prefix = query;
	        suggestWords(prefix,crawl);
	        return 1;
	    }
	    return 0;
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

int main(){
	Trie trie;
    string dictionary[100];
    int ch;
    string word;

    while (true)
    {
        cout << "\n";
        cout << "1. Add Word to Dictionary.\n2.Check if a Word is present in the Dictionary.\n3.Get all the words with the given Prefix.\n4.Print the Dicionary.\n5.Exit" << '\n';
        cout << "\n";
        cin >> ch;

        switch (ch)
        {
        case 1: {
            cout << "Enter Word: ";
            cin >> word;
            trie.insert_word(word, 5);
            cout << "\n";
            cout << "Word Inserted !" << '\n';
            break;
        }
        case 2: {
            cout << "Enter Word: ";
            cin >> word;
            cout << "\n";
            (trie.search_word(word)) ? cout << "Word Found in the Dictionary!" << '\n' : cout << "Word not found in the Dictionary." << '\n';
            cout << "\n";
            break;
        }
        case 3: {
            cout << "Enter Prefix: ";
            cin >> word;
            cout << "\n";
            int res = trie.autoSuggest(word);
            if (res == -1) {
                cout << "No word other than the Prefix found in the Dictionary." << '\n';
            } else if (!res) {
                cout << "No words found with this in the Dictionary." << '\n';
            }
            break;
        }
        case 4:{
            trie.printDictionary();
            break;
        }
        case 5:{
            exit(0);
            break;
        }
        default:{
            cout << "Choice not available." << '\n';
            break;
        }
    }
}
	return 0;
}

