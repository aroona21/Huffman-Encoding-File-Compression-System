#include "HuffmanEncoder.h"

// ----GLOBAL FILE I/O IMPLEMENTATION----

// to read content from file (task 1)
string readFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return "";
    }
    // to read the entire stream buffer into a string 
    string content((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));
    return content;
}

// to write content to a file (task 6)
void writeFile(const string& filename, const string& content) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return;
    }
    outputFile << content;
}


// ----HUFFMAN ENCODER & DECODER IMPLEMENTATION----

HuffmanEncoder::~HuffmanEncoder() {
    delete root;
}

// calculates character frequency count (task 2)
void HuffmanEncoder::updateFrequency(char ch) {
    bool found = false;
    for (int i = 0; i < freqCount; ++i) {
        if (frequencies[i].ch == ch) {
            frequencies[i].freq++;
            found = true;
            break;
        }
    }
    // if the character is encountered for the first time, initialize its entry
    if (!found) {
        frequencies[freqCount].ch = ch;
        frequencies[freqCount].freq = 1;
        freqCount++;
    }
}

// to sort frequencies by descending count using bubble sort (task 2)
void HuffmanEncoder::sortFrequencies() {
    for (int i = 0; i < freqCount - 1; ++i) {
        for (int j = 0; j < freqCount - i - 1; ++j) {
            if (frequencies[j].freq < frequencies[j + 1].freq) {

                FreqPair temp = frequencies[j];
                frequencies[j] = frequencies[j + 1];
                frequencies[j + 1] = temp;
            }
        }
    }
}

// to build the Huffman tree (Task 3)
void HuffmanEncoder::buildHuffmanTree() {
    // using min-heap (priority queue)
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // non-zero frequency as leaf nodes
    for (int i = 0; i < freqCount; ++i) {
        if (frequencies[i].freq > 0) {
            minHeap.push(new Node(frequencies[i].ch, frequencies[i].freq));
        }
    }

    // huffman tree construction loop
    while (minHeap.size() > 1) {

        // two nodes with smallest frequency
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        // create parent node with combined frequency
        int sumFreq = left->freq + right->freq;
        Node* parent = new Node('\0', sumFreq, left, right);

        minHeap.push(parent);
    }

    // the final node is the root
    if (!minHeap.empty()) {
        root = minHeap.top();
    }
    else {
        root = nullptr;
    }
}

// to generate codes (task 4)
void HuffmanEncoder::generateCodes(Node* curr, string code) {
    // Base Case (if the current node is a leaf, the code is complete)
    if (curr->left == nullptr && curr->right == nullptr) {
        codes[codeCount].ch = curr->ch;
        codes[codeCount].code = code;
        codeCount++;
        return;
    }

    // if moving left (append '0')
    if (curr->left) {
        generateCodes(curr->left, code + "0");
    }
    // if moving right (append '1')
    if (curr->right) {
        generateCodes(curr->right, code + "1");
    }
}

// to get code for a character
string HuffmanEncoder::getCode(char ch) const {
    for (int i = 0; i < codeCount; ++i) {
        if (codes[i].ch == ch) {
            return codes[i].code;
        }
    }
    return "";
}

// encode text (task 5)
string HuffmanEncoder::encode(const string& text) {
    if (text.empty()) return "";

    // (task 2)
    for (char c : text) {
        updateFrequency(c);
    }
    sortFrequencies();

    // (task 3)
    buildHuffmanTree();

    // (task 4)
    generateCodes(root, "");

    // encode text
    string encodedBitString = "";
    for (char c : text) {
        encodedBitString += getCode(c);
    }
    return encodedBitString;
}

// decode data (task 7)
string HuffmanEncoder::decode(const string& encodedBitString) {
    if (!root || encodedBitString.empty()) return "";

    string decodedText = "";
    Node* current = root;

    // Traversing the tree
    for (char bit : encodedBitString) {
        if (bit == '0') {
            current = current->left;
        }
        else {         // bit == '1'
            current = current->right;
        }

        // when a leaf node is reached, a full character has been decoded
        if (current && current->left == nullptr && current->right == nullptr) {
            decodedText += current->ch;
            current = root; // reset traversal to the root 
        }
    }
    return decodedText;
}

// Prints the tree sideways (Right child printed first)
void HuffmanEncoder::printTreeRecursive(ostream& os, Node* curr, int level) const {
    if (curr == nullptr) {
        return;
    }

    // Traverse Right('1')
    printTreeRecursive(os, curr->right, level + 1);

    for (int i = 0; i < level; ++i) {
        os << "    ";
    }

    if (level > 0) {
        os << "|-- ";
    }

    if (curr->ch == '\0') {
        os << "(" << curr->freq << ")\n";
    }
    else {
        char displayChar = curr->ch;
        if (displayChar == '\n') os << "[\\n, " << curr->freq << "]\n";
        else if (displayChar == ' ') os << "[Spc, " << curr->freq << "]\n";
        else if (displayChar == '\t') os << "[\\t, " << curr->freq << "]\n";
        else os << "[" << displayChar << ", " << curr->freq << "]\n";
    }

    // Traverse Left('0')
    printTreeRecursive(os, curr->left, level + 1);
}

void HuffmanEncoder::displayTree(ostream& os) {
    os << "\n--- Huffman Binary Tree Structure (Sideways) ---\n";
    os << "Note: Right branch = '1' path, Left branch = '0' path\n";
    if (root == nullptr) {
        os << "Tree is empty (Input was empty).\n";
        os << "--------------------------------------------------------\n";
        return;
    }
    printTreeRecursive(os, root, 0);
    os << "--------------------------------------------------------\n";
}

void HuffmanEncoder::displayFrequencies(ostream& os) {
    os << "\n--- Character Frequencies (Sorted) ---\n";
    os << "Char | ASCII | Frequency\n";
    os << "-----------------------------------\n";
    for (int i = 0; i < freqCount; ++i) {
        char displayChar = frequencies[i].ch;
        if (displayChar == '\n') os << " \\n  |";
        else if (displayChar == ' ') os << " Spc |";
        else if (displayChar == '\t') os << " \\t  |";
        else os << "  " << displayChar << "  |";

        os << " " << (int)displayChar << "   | " << frequencies[i].freq << "\n";
    }
    os << "-----------------------------------\n";
}

void HuffmanEncoder::displayCodes(ostream& os) {
    os << "\n--- Huffman Codes (The Dictionary) ---\n";
    os << "Char | Code\n";
    os << "-----------------------------------\n";
    for (int i = 0; i < codeCount; ++i) {
        char displayChar = codes[i].ch;
        if (displayChar == '\n') os << " \\n  |";
        else if (displayChar == ' ') os << " Spc |";
        else if (displayChar == '\t') os << " \\t  |";
        else os << "  " << displayChar << "  |";

        os << " " << codes[i].code << "\n";
    }
    os << "-----------------------------------\n";
}

// display Compression Statistics (task 8)
void HuffmanEncoder::displayStats(ostream& os, int originalLength, int compressedLength) {
    double originalBits = originalLength * 8.0; //  8-bit ASCII standard

    double compressionRatio = (1.0 - (double)compressedLength / originalBits) * 100.0;

    os << "\n--- Compression Statistics (Task 8) ---\n";
    os << "Original Character Count: " << originalLength << " chars\n";
    os << "Original File Size (8-bit ASCII): " << originalBits << " bits\n";
    os << "Compressed Bit Stream Length: " << compressedLength << " bits\n";

    os << "Estimated Compressed Size (Bytes): " << (compressedLength + 7) / 8 << " bytes\n";

    os.precision(2);    // compression ratio with 2 decimal places

    os << "Compression Ratio (Reduction): " << fixed << compressionRatio << " %\n";
    os << "----------------------------------\n";
}