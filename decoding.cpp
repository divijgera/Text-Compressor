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

	HuffmanTreeNode(){
		left = NULL;
		right = NULL;
	}

	~HuffmanTreeNode(){
		delete left;
		delete right;
	}
};


string read_file(const string& file_name){
	string text;
	ifstream input_stream(file_name, ios::in | ios::binary);
	if(!input_stream){
		return "";
	}
	do{
		int c= input_stream.get();
		if (c==EOF){
			break;
		}
		text += (char)c;
	}
	while(!input_stream.fail());
	return text;
}
void save_text_to_file(const string& text, const string& file_name){
	ofstream OutFile;
	OutFile.open(file_name, ios::out | ios::binary);
	OutFile << text;
	OutFile.close();
}


string int_to_bits_converter(unsigned int num){
	string bits = "00000000";
	for(int i=7;i>=0;i--){
		bits[i] = num%2 + '0';
		num = num >> 1;
	}
	return bits;
}

int bits_to_int_converter(const string& bits){
	int ans = 0;
	for(int i=0;i<bits.size();i++){
		ans = ans << 1;
		ans += bits[i] - '0';
	}
	return ans;
}

string remove_prefix_suffix(string bits){
	string prefix = bits.substr(0,8);
	int extra_bits = bits_to_int_converter(prefix);

	while(extra_bits%8 != 0){
		bits.pop_back();
		extra_bits++;
	}

	return bits.substr(8);

}


string encoded_text_to_bits(string encoded_text){
	string bits = "";
	for(unsigned int i=0;i<encoded_text.length();i++){
		unsigned int letter = encoded_text[i];
		bits = bits + int_to_bits_converter(letter);
	}

	bits = remove_prefix_suffix(bits);
	return bits;
}


HuffmanTreeNode* buildHuffmanTree(string map_text){
	HuffmanTreeNode* root = new HuffmanTreeNode();
	HuffmanTreeNode* temp = root;

	istringstream f(map_text);
    string code;
    string char_line;
    char character;

    while(std::getline(f,code) && std::getline(f,char_line)){
    	if(char_line==""){
    		std::getline(f,char_line);
    		char_line = "\n";
    	}

    	character = char_line[0];

    	for(unsigned int i = 0; i<code.length();i++){
    		if(code[i] == '0'){
    			if(temp->left == NULL){
    				HuffmanTreeNode* child_node = new HuffmanTreeNode();
    				temp->left = child_node;
    			}
    			temp = temp->left;
    		}
    		else if(code[i] == '1'){
    			if(temp->right == NULL){
    				HuffmanTreeNode* child_node = new HuffmanTreeNode();
    				temp->right = child_node;
    			}
    			temp = temp->right;
    		}

    		temp->text.push_back(character);
    	}

    	temp = root;
    }
    return root;
}


string decode_bits(string encoded_bits, HuffmanTreeNode* root){
	HuffmanTreeNode* temp = root;
	string original_text;

	for(unsigned int i=0;i<=encoded_bits.length();i++){
		if(temp->right == NULL && temp->left == NULL){
			original_text += temp->text;
			temp = root;
			i--;
		}
		else if(encoded_bits[i] == '0'){
			temp = temp->left;
		}
		else if(encoded_bits[i] == '1'){
			temp = temp->right;
		}
	}

	return original_text;
}


int main(int argc, char**argv){
	if(argc < 4){
        return -1;
	}

    string encoded_text = read_file(argv[1]);
    if(encoded_text == ""){
        return -1;
    }

    string encoded_bits = encoded_text_to_bits(encoded_text);

    string map_text = read_file(argv[2]);
    if(map_text == ""){
        return -1;
    }

    HuffmanTreeNode* root = buildHuffmanTree(map_text);
    string original_text = decode_bits(encoded_bits,root);
    save_text_to_file(original_text, argv[3]);
    delete root;
    return 0;
}