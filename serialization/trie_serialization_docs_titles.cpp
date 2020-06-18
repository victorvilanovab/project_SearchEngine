#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <typeinfo>
#include <chrono>
#include <iterator>
#define alpha_size 30
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
using namespace std;
string word;

vector<string> merge(vector<string> a, vector<string> b){
	vector<string> c;
	c=a;
	for (int i=0; i<b.size(); i++){
	if (find(a.begin(), a.end(), b[i]) != a.end()){
	}
	else{
			c.push_back(b[i]);
		}
	}
	return c;
}

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

struct TrieNode {
    bool EndOfWord;
    vector<string> documents;
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
	
//	void insert_doc(string page, int doc){
//	int init, end;
//	int letter = 0;
//	while (letter < page.length()) {
//		while (page[letter] == ' ' && letter < page.length()) letter++;
//		init = letter;
//		while (page[letter] != ' ' && letter < page.length()) letter++;
//		end = letter - 1;
//		if (init <= end){
//			string word = page.substr(init, end - init + 1);
//			word = removeSpaces(word);
//			insert_word(word, doc);
//			}
//		}
//	}
//		
//	
//	
//	// Insert a word into a Trie.
//	void insert_word(string key, int doc) {
//	    TrieNode *crawl = root;
//	
//	    for (int t = 0; t < key.length(); t++) {
//	        int index = key[t] - 'a';
//	
//	        if (!crawl->children[index]) {
//	            crawl->children[index] = createNode();
//	        }
//	
//	        crawl = crawl->children[index];
//	        // crawl->freq++; Uncomment for Count of every node hit count.
//	    }
//	    crawl->freq++;  // For the count of word hit count.
//	    crawl->EndOfWord = true;
//	    if (find(crawl->documents.begin(), crawl->documents.end(), doc) != crawl->documents.end()){
//		}
//		else{
//		//	crawl->documents.push_back(doc);
//		}
//	}
	
	// Insert word with vector
	void insert_word_vector(string key, vector<string> doc) {
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
		crawl->documents = merge(crawl->documents, doc);
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
	
vector<string> suggestWords(string prefix, TrieNode *root, vector<string> vetor) {
    if (root->EndOfWord == true){
        vetor.push_back(prefix);
    }

    if (isLastNode(root)) {
        return vetor;
    }

    for (int t = 0; t < alpha_size; t++) {
        if (root->children[t]) {
            prefix.push_back(97 + t);
            vetor = suggestWords(prefix, root->children[t], vetor);
            prefix.pop_back();
        }
    }
    return vetor;
}

vector<string> autoSuggest(const string query, vector<string> vetor) {
    TrieNode *crawl = root;
    int level;
    int n = query.length();

    for (level = 0; level < n; level++) {
        int ind = CHAR_TO_INDEX(query[level]);

        if (!crawl->children[ind]){
         //entra aqui se nao existe o postfixo
            return vetor;}

        crawl = crawl->children[ind];
    }

    bool isWord = (crawl->EndOfWord == true);
    bool isLast = isLastNode(crawl);

    if (isWord && isLast) {
         // entra aqui se ja e uma palavra existente
        return vetor;
    }

    if (!isLast) {
        string prefix = query;
        vetor = suggestWords(prefix, crawl, vetor);
       // entra aqui quando existe o postfixo
        return vetor;
    }
    return vetor;
}

	void serialization_trie(fstream &file) {
	    if (root->EndOfWord){
	    	vector<string> g1=root->documents;
	    	file << "&"+word << endl;
		if (g1.size() != 1) {
	for(int i=0; i < g1.size(); i++){
		if(i==0){
			file << g1[i]+ " ";
		}
		if(i!=0 && i!=g1.size()-1){
      		file << g1[i]+ " ";
		}
        if(i==g1.size()-1){
			file << g1[i]+ " ";
		}
  	}
}
	else {
		file << g1[0];
}
	file << "\n";	
   }
	
	    if (isLastNode(root))
	        return;
	
	    for (int t = 0; t < alpha_size; t++) {
	        if (root->children[t]) {
	            word.push_back(97 + t);
	            serialization_trie(root->children[t], file);
	            word.pop_back();
	        }
	    }
	    return;
	}
	
	void serialization_trie(TrieNode *root, fstream &file) {
	    if (root->EndOfWord){
	    	vector<string> g1=root->documents;
	    	file << "&"+word << endl;
		if (g1.size() != 1) {
	for(int i=0; i < g1.size(); i++){
		if(i==0){
			file << g1[i] + " ";
		}
		if(i!=0 && i!=g1.size()-1){
      		file <<  g1[i] + " ";
		}
        if(i==g1.size()-1){
			file <<  g1[i] + " ";
		}
  	}
}
	else {
		file <<  g1[0];
}
	file << "\n";
	}
	
	    if (isLastNode(root))
	        return;
	
	    for (int t = 0; t < alpha_size; t++) {
	        if (root->children[t]) {
	            word.push_back(97 + t);
	            serialization_trie(root->children[t], file);
	            word.pop_back();
	        }
	    }
	    return;
	}
	
	
	
	void read_serialization(fstream &file){
	string line;
	string word;
	int i=1;
	while (getline(file,line)){
		if (line[0] == '&'){
			line.erase(0,1);
			word = line;
		}
		else{ 
			vector<string> docs;
			split1(line , docs);
			if (i%2 == 0){
				insert_word_vector(word,docs);
		}
	}
	i+=1;	
	}
}
			
};



std::vector<std::string> intersection(std::vector<std::string> &v1,
                                      std::vector<std::string> &v2){
    std::vector<std::string> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}

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
	string path2 = "C:\\Users\\Victor Vilanova\\Desktop\\";
	fstream file;
	file.open(path2+"serialization_docs.txt");
	fstream file2;
	file2.open(path2+"serialization_titles.txt");
	cout << "Opening the tree from txt serialization file." << endl;
	auto t1 = std::chrono::steady_clock::now();
	trie.read_serialization(file2);
	trie.read_serialization(file);
	auto t2 = std::chrono::steady_clock::now();
    auto duration = chrono::duration <double, milli> (t2 - t1).count();
    file.close();
    file2.close();
    cout << "Time to creating the tree: " << duration << endl;
    fstream serialize;
    serialize.open(path2+"serialization_docs_titles.txt");
    auto tt1 = std::chrono::steady_clock::now();
    trie.serialization_trie(serialize);
    auto tt2 = std::chrono::steady_clock::now();
    auto duration2 = chrono::duration <double, milli> (tt2 - tt1).count();
    cout << "Time creating the serialization file: "<< duration2 << endl;
    cout << "FINISHED!" << endl;
//	while(1){
//		cout << "\n";
//        cout << "1. Enter a word to query.\n2.Exit" << '\n';
//        cout << "\n";
//		int ch;
//		cin >> ch;
//		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//		switch (ch)
//        {
//        case 1: {
//            cout << "Enter Word: " << endl;
//            string palavra;
//			getline(cin, palavra);
//            transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);
//            vector<string> words; // words é um vector de palavras da busca
//            search_again:
//            split1(palavra,words);
//            for( int i =0; i<words.size();i++){
//            	cout << "!" << words[i] << "! "<< endl;
//			}
//            int n_words = words.size();
//            int aux = 0;
//            auto t1 = std::chrono::steady_clock::now();
//            for (int i = 0; i< n_words; i++){
//				if(trie.search_word(words[i])){
//				aux+=1;
//				}
//			}
//            auto t2 = std::chrono::steady_clock::now();
//            auto duration = chrono::duration <double, milli> (t2 - t1).count();
//            vector<string> intersecao = trie.search_word_node(words[0])->documents;
//            for(int k=1; k<n_words; k++){
//            	intersecao = intersection(intersecao, trie.search_word_node(words[k])->documents);
//			}
//            if (aux==n_words && intersecao.size() != 0){
//            	cout << "Searching..." << endl;
//            	cout << "Time of serach : " << duration<< endl;
//            	cout << "We match " << intersecao.size() << "docs for your search." << endl;
//            	vector<string> x = intersecao;
//				string line;
//				int n_print;
//				if (intersecao.size() < 20){
//				n_print=intersecao.size();
//				}
//				else{
//					n_print=20;
//				}
//            	for (int i=0; i< n_print;i++){
//            		ifstream file_doc (path +"/titles/doc_"+x[i]+".txt");
//            		while (getline(file_doc, line)){
//            		cout << "["<< x[i] << "] = " ;
//					cout << line << endl;
//					}
//            	file_doc.close();
//            	}
//            	if (intersecao.size()<20){
//            		cout << "You saw all of the documents for the word(s)." << endl;
//				}
//            	while(intersecao.size()>20){
//            		n_print=20;
//            		print:
//            		if (n_print <= intersecao.size()){
//            		cout << "Do you want to see more titles of the documents? type(1/0)" << endl;
//            	}
//            	int ch;
//            	cin >> ch;
//            		switch(ch){
//            			case 1: {
//            				n_print+=20;
//            				if (n_print >= intersecao.size()){
//							}
//            				if (n_print >= intersecao.size()){
//            					int new_print = intersecao.size() - (n_print - 20);
//            					for (int i=n_print-20; i< intersecao.size();i++){
//            				ifstream file_doc (path +"/titles/doc_"+x[i]+".txt");
//            				while (getline(file_doc, line)){
//            				cout << "["<< x[i] << "] = " ;
//							cout << line << endl;
//					}
//            	file_doc.close();
//            }
//            cout << "You saw all of the documents for the word(s)." << endl;
//							}
//							else{
//            				for (int i=n_print-20; i< n_print;i++){
//            				ifstream file_doc (path +"/titles/doc_"+x[i]+".txt");
//            				while (getline(file_doc, line)){
//            				cout << "["<< x[i] << "] = " ;
//							cout << line << endl;
//					}
//            	file_doc.close();
//            }
//            goto print;
//							}
//						}
//						case 0: {
//							break;
//						}
//						default:
//            				cout << "Choice not available." << '\n';
//				}
//			break;
//			}
//			while(1){
//				cout << "\n";
//				cout << "Do you want to open any of the documents? type(1/0)";
//				cout << "\n";
//				int ch;
//				cin >> ch;
//				switch(ch)
//				{
//				case 1: {
//					cout << "Which of the documents do you want to open? type(number of document)";
//					cout << "\n";
//					int ch;
//					cin >> ch;
//					string line;
//					string title;
//					ifstream file_title (path+"/titles/doc_"+to_string(ch)+".txt");
//					getline(file_title, title);
//					cout << title << endl;
//					ifstream file_doc (path+"/docs/doc_"+to_string(ch)+".txt");
//					while (getline(file_doc, line)){
//					cout << line << endl;
//					}
//				break;
//				}
//				case 0:{
//					break;
//				}
//				default:
//            		cout << "Choice not available." << '\n';
//				}
//				break;
//			}
//		}
//		else {
//			cout << "Do you mean?" << endl;
//			vector<string> words_sugestions;
//			words_sugestions = trie.autoSuggest(words[0], words_sugestions);
//			int x=0;
//			for (int i=0; i < words_sugestions.size(); i++){
//				cout << "[" << x << "]" << " = " << words_sugestions[i] << endl;
//				x+=1;
//			}
//			ask_again:
//				cout << "Do you want to search any of these words? type(1/0)" << endl;
//				int ch;
//				cin >> ch;
//				if (ch == 1){
//						cout << "Which of the words? type(number of word)" << endl;
//						int num;
//						cin >> num;
//						string palavra_new;
//						palavra_new = words_sugestions[num];
//						palavra.clear();
//						words.clear();
//						palavra=palavra_new;
//						cout << "You choose to search :" << palavra << endl;
//						goto search_again;
//					}
//					if( ch == 0){
//					}
//					if( ch != 0 && ch != 1){
//						cout << "Choice not avaible." << endl;
//						goto ask_again;
//				}
//		}
//           	break;
//		}
//            	
//        case 2:{
//        	exit(0);
//			break;
//		}
//        
//        default:
//            cout << "Choice not available." << '\n';
//        }
//	}
	return 9;
}


