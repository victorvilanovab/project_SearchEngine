#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#define alpha_size 40
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

string removeSpaces(string str)
{ 
    for(int i = 0; i < str.size(); ++i)
    {
        if (!((str[i] >= 'a' && str[i]<='z')))
        {
            str[i] = ' ';
        }
    }
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
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
			word = removeSpaces(word);
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
	Trie trie;
    int number_doc=0;
    string doc;
    string path = "C:\\Users\\Victor Vilanova\\Documents\\Search_Engine_Git\\project_SearchEngine\\cleaning_data\\test_clean_data";
	ifstream file;
	auto t1 = std::chrono::steady_clock::now();
	while( number_doc <= 19 ){
		file.open(path +"\\clean_docs\\doc_"+to_string(number_doc)+".txt");
		if (file.is_open()) {
			if (file.good()) {
				    while(getline(file, doc)){
					trie.insert_doc(doc, number_doc);
					}
			}
		}
		file.close();
		number_doc+=1;
	}
	auto t2 = std::chrono::steady_clock::now();
    auto duration = chrono::duration <double, milli> (t2 - t1).count();
    cout << "Time creating the Trie: "<< duration << endl;
	
	while(1){
		cout << "\n";
        cout << "1. Enter a word to query.\n2.Exit" << '\n';
        cout << "\n";
        int ch;
		cin >> ch;
		switch (ch)
        {
        case 1: {
            cout << "Enter Word: ";
            cin >> word;
            transform(word.begin(), word.end(),word.begin(), ::tolower);
            cout << "\n";
            cout << "Searching..." << endl;
            auto t1 = std::chrono::steady_clock::now();
            bool search = trie.search_word(word);
            auto t2 = std::chrono::steady_clock::now();
            auto duration = chrono::duration <double, milli> (t2 - t1).count();
            if (search){
            	cout << "Time of serach : " << duration<< endl;
            	vector<int> x = trie.search_word_node(word)->documents;
				string line;
            	for (int i=0; i<x.size();i++){
            		ifstream file_doc (path +"/titles_docs/doc_"+to_string(x[i])+".txt");
            		while (getline(file_doc, line)){
            		cout << "["<< x[i] << "] = " ;
					cout << line << endl;
					}
            	file_doc.close();
            	}
			while(1){
				cout << "\n";
				cout << "Do you want to open any of the documents? type(1/0)";
				cout << "\n";
				int ch;
				cin >> ch;
				switch(ch)
				{
				case 1: {
					cout << "Which of the documents do you want to open? type(number of document)";
					cout << "\n";
					int ch;
					cin >> ch;
					string line;
					string title;
					ifstream file_title (path+"/titles_docs/doc_"+to_string(ch)+".txt");
					getline(file_title, title);
					cout << title << endl;
					ifstream file_doc (path+"/docs/doc_"+to_string(ch)+".txt");
					while (getline(file_doc, line)){
					cout << line << endl;
					}
				break;
				}
				case 0:{
					break;
				}
				default:
            		cout << "Choice not available." << '\n';
				}
				break;
			}
		}
           	break;
		}
            	
        case 2:{
        	exit(0);
			break;
		}
        
        default:
            cout << "Choice not available." << '\n';
        }
	}
	return 9;
}


