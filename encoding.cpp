#include<bits/stdc++.h>
using namespace std;
#define ll long long

// A Huffman Tree Node class which contains a string value and frequency for each node
class HuffmanTreeNode{
public:
	string text;
	ll freq;
	HuffmanTreeNode* left;
	HuffmanTreeNode* right;
	HuffmanTreeNode(string s, ll freq){
		text = s;
		this->freq = freq;
		left = NULL;
		right = NULL;
	}

	~HuffmanTreeNode(){
		delete left;
		delete right;
	}
};


class comp{
public:
	bool operator()(const HuffmanTreeNode* a, const HuffmanTreeNode* b){
		return a->freq > b->freq;
	}
};


string int_to_bits_converter(unsigned int extrabits){
	string ans = "00000000";
	for(int i=7;i>=0;i--){
		ans[i] = extrabits%2 + '0';
		extrabits = extrabits >> 1;
	}
	return ans;
}


HuffmanTreeNode* buildHuffmanTree(string s){

	//Storing the freq of each character in a map
	unordered_map<char,int> m;
	for(ll i=0;i<s.length();i++){
		if(m.count(s[i])==0){
			m[s[i]] = 1;
		}
		else{
			m[s[i]]++;
		}
	}


	//Iterating over the map and adding each character as a HuffmanTreeNode in the minimum priority queue
	priority_queue<HuffmanTreeNode*,vector<HuffmanTreeNode*>,comp> pq;
	unordered_map<char,int>::iterator it = m.begin();
	for(;it!=m.end();it++){
		string text(1,it->first);
		ll value = it->second;
		HuffmanTreeNode* node = new HuffmanTreeNode(text,value);
		pq.push(node);
	}


	//Creating a tree
	while(pq.size()!=1){
		HuffmanTreeNode* node1 = pq.top();
		pq.pop();
		HuffmanTreeNode* node2 = pq.top();
		pq.pop();

		string text = node1->text + node2->text;
		ll freq = node1->freq + node2->freq;
		// cout<<text<<endl;
		HuffmanTreeNode* newNode = new HuffmanTreeNode(text,freq);
		newNode->left = node1;
		newNode->right = node2;
		pq.push(newNode);
	}

	return pq.top();

}


void encoder(HuffmanTreeNode* root, unordered_map<char,string>& encodings, string code){
	if(root==NULL){
		return;
	}

	if(root->left==NULL && root->right == NULL){
		char text = root->text[0];
		encodings[text] = code;
		return;
	}

	encoder(root->left,encodings,code+'0');
	encoder(root->right,encodings,code+'1');
}



unordered_map<char,string> code_generator(HuffmanTreeNode* root){
	unordered_map<char,string> encodings;
	encoder(root,encodings,"");
	return encodings;
}


string add_prefix_suffix(string code){
	int prefix = (code.length())%8;
	string pre= int_to_bits_converter(prefix);
	code = pre + code;
	
	while(code.length()%8 != 0){
		code += '0';
	}

	return code;
}


string encode_text(string bits){
	string final_string;
	unsigned int sum = 0;
    for(unsigned int i=0;i<bits.size();i++) {
        sum = sum << 1;
        sum += (bits[i]  - '0');

        if((i+1)%8==0) {
            final_string += (unsigned char)sum;
            sum = 0;
        }
    }

    return final_string;
}

string huffman_code(const string& s, unordered_map<char,string> encodings){
	string code;
	for(unsigned int i=0;i<s.length();i++){
		string temp = encodings[s[i]];
		code+=temp;
	}
	code = add_prefix_suffix(code);
	code = encode_text(code);
	return code;
}




string read_file(const string& file_name) {

    string text;
    ifstream input_stream(file_name, ios::in | ios::binary);

	if(!input_stream)
		return "";

    do {
        int c= input_stream.get();
        if (c==EOF) break;
        text += (char)c;
    } while (!input_stream.fail());

    return text;
}

void save_text_to_file(const string& text, const string& file_name) {

    ofstream OutFile;
    OutFile.open(file_name, ios::out | ios::binary);

    OutFile << text;
    OutFile.close();
}

string create_map_string(unordered_map<char,string> encodings){
	string map_string;
	unordered_map<char,string>::iterator it = encodings.begin();
	for(;it!=encodings.end();it++){
		map_string += it->second + "\n" + it->first + "\n";
	}
	return map_string;
}



int main(int argc, char** argv){
	if(argc < 4){
        return -1;
	}

    string original_text = read_file(argv[1]);
    if(original_text == ""){
        return -1;
    }

	HuffmanTreeNode* root = buildHuffmanTree(original_text);
	unordered_map<char,string> encodings = code_generator(root);
	string code = huffman_code(original_text,encodings);
	save_text_to_file(code, argv[2]);
	string map_string = create_map_string(encodings);
	save_text_to_file(map_string, argv[3]);
	delete root;

	return 0;
}