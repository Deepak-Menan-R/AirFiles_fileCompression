 //Header Guards to prevent header files from being included multiple times
#ifndef AIRFILE_HPP
#define AIRFILE_HPP
#include <string>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

//Defining AirFile Tree Node
struct Node {
    char data;
    unsigned freq;
    string code;
    Node *left, *right;

    Node() {
        left = right = NULL;
    }
};

class AirFile {
    private:
        vector <Node*> arr;

        fstream inFile, outFile;

        string inFileName, outFileName;
        
        Node *root;
        
        class Compare {
            public:
                bool operator() (Node* l, Node* r)
                {
                    return l->freq > r->freq;
                }
        };

        priority_queue <Node*, vector<Node*>, Compare> minHeap;
        
        //Initializing a vector of tree nodes representing character's ascii value and initializing its frequency with 0
        void createArr();
        
        //Traversing the constructed tree to generate AirFile codes of each present character
        void traverse(Node*, string);
        
        //Function to convert binary string to its equivalent decimal value
        int binToDec(string);
        
        //Function to convert a decimal number to its equivalent binary string
        string decToBin(int);
        
        //Reconstructing the AirFile tree while Decoding the file
        void buildTree(char, string&);

        //Creating Min Heap of Nodes by frequency of characters in the input file
        void createMinHeap();
        
        //Constructing the AirFile tree
        void createTree();
        
        //Generating AirFile codes
        void createCodes();
        
        //Saving AirFile Encoded File
        void saveEncodedFile();
        
        //Saving Decoded File to obtain the original File
        void saveDecodedFile();
        
        //Reading the file to reconstruct the AirFile tree
        void getTree();

    public:
        //Constructor
        AirFile(string inFileName, string outFileName)
        {
            this->inFileName = inFileName;
            this->outFileName = outFileName;
            createArr();
        }
        //Compressing input file
        void compress();
        //Decrompressing input file
        void decompress();
};
#endif