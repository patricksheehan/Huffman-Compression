// Patrick Sheehan

#include "huff.h"
#include <iostream>
#include <cstring>

void compress();
void putOut();
void decompress();
Node * constructHeap();
unsigned int frequencies[256] = {0};
string codebook[256];

int main(int argc, char* argv[]) {
    if(argc == 2){
        if((argv[1][0] == '-') && (argv[1][1] == 'd'))
            decompress();
    }
    else
        compress();
    return 0;
}

void compress(){ 
    unsigned char nextChar;
    // first, calculate the frequencies of each character
    cin >> noskipws;
    while(cin >> nextChar)
        frequencies[nextChar]++;
    
    
    Node * root = constructHeap();
    string code;
    root->fillCodebook(codebook,code);
    
    putOut();
}

void putOut(){
    cout<< "HUFFMA3" << '\0';
    
    unsigned int i;
    for(i = 0; i < 256; i++){
        cout<<(char) (0x000000ff & frequencies[i]);
        cout<<(char) ((0x0000ff00 & frequencies[i]) >> 8);
        cout<<(char) ((0x00ff0000 & frequencies[i]) >> 16);
        cout<<(char) ((0xff000000 & frequencies[i]) >> 24);
    }
   
    unsigned char nextChar;
    char nextByte = 0;
    int bitCounter = 0;
    
    cin.clear();
    cin.seekg(0);
    cin >> noskipws;
    while(cin >> nextChar){
        for(i = 0; i < codebook[nextChar].size(); i++, bitCounter++){
            if(bitCounter == 8){
                cout<< nextByte;
                nextByte = 0;
                bitCounter = 0;
            }
            if(codebook[nextChar][i] == '1')
                nextByte = nextByte | (0x01 << bitCounter);
        }
    }
    if(bitCounter)
        cout << nextByte;
}

void decompress(){
    cin >> noskipws;
    char magic[8];
    cin.read(magic,8);
    char nextByte;
    for(int i = 0; i < 256; i++){
        cin.read((char *)&frequencies[i],4);
    }
    
    Node * root = constructHeap();
    string code;
    root->fillCodebook(codebook,code);

    while(cin>>nextByte){
        for(int i = 0; i < 8; i++){
            if((nextByte >> i) & 0x01)
                code += '1';
            else
                code += '0';
            for(int i = 0; i < 256; i++){
                if(codebook[i] == code){
                    if(frequencies[i]){
                              cout << (unsigned char) i;
                              code.clear();
                              frequencies[i]--;
                              break;
                    }
                    else
                        return;
                }
            } // for
        }
    }
    
        
}

Node * constructHeap(){
    Heap minHeap;
    Node *nextNode;
    for(int i = 0; i < 256; i++){
        if (frequencies[i]){
            nextNode = new Node(i, frequencies[i]);
            minHeap.push(nextNode);
        }
    }
    
    Node * node1;
    Node * node2;
    Node * merged;
    while(minHeap.size() > 1){
        node1 = minHeap.top();
        minHeap.pop();
        node2 = minHeap.top();
        minHeap.pop();
        merged = new Node(node1, node2);
        minHeap.push(merged);
    }
    
    return minHeap.top();
}
