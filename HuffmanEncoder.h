#pragma once
#ifndef HUFFMANENCODER_H
#define HUFFMANENCODER_H

#include <iostream> 
#include <fstream>  
#include <queue>    
#include <vector>   
#include <string>   

using namespace std;

// ----DATA STRUCTURE DEFINITIONS----

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f, Node* l = nullptr, Node* r = nullptr)
        : ch(c), freq(f), left(l), right(r) {
    }

    ~Node() {
        delete left;
        delete right;
    }
};

// priority queue for min heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

struct FreqPair {
    char ch;
    int freq;
};

struct CodePair {
    char ch;
    string code;
};


// ----HUFFMAN ENCODER & DECODER CLASS----

class HuffmanEncoder {
private:
    Node* root = nullptr;

    CodePair codes[256];
    FreqPair frequencies[256];

    int codeCount = 0;
    int freqCount = 0;


    // task 2
    void updateFrequency(char ch);

    // task 2
    void sortFrequencies();

    // task 3
    void buildHuffmanTree();

    // task 4
    void generateCodes(Node* curr, string code);

    string getCode(char ch) const;

    void printTreeRecursive(ostream& os, Node* curr, int level) const;

public:
    ~HuffmanEncoder();

    string encode(const string& text);
    string decode(const string& encodedBitString);

    // task 2
    void displayFrequencies(ostream& os);

    // task 4
    void displayCodes(ostream& os);

    void displayTree(ostream& os);

    // task 8
    void displayStats(ostream& os, int originalLength, int compressedLength);
};

// ----GLOBAL FILE UTILITIES----

// task 1
string readFile(const string& filename);

// task 6
void writeFile(const string& filename, const string& content);

#endif