****Huffman Encoding Project****

**Overview**

This project implements the Huffman Encoding Algorithm in C++ as part of a Data Structures and Algorithms (DSA) course. Huffman Encoding is a lossless data compression technique that assigns variable-length binary codes to characters based on their frequencies, reducing the overall size of the data.

**Features**

* Builds a Huffman Tree from character frequencies.
* Generates Huffman codes for each character.
* Compresses text into binary format.
* Decompresses the compressed data back to the original text.
* Generates a report containing character frequencies and Huffman codes.

**Project Structure**

```
Huffman-Encoding-Project/
│
├── README.md
├── DSA Project Report.pdf
├── Flowchart.png
│
└── Code/
    ├── main.cpp
    ├── HuffmanEncoder.cpp
    ├── HuffmanEncoder.h
    ├── input.txt
    ├── compressed_bits.txt
    ├── output_decompressed.txt
    └── huffman_report.txt
```

**Technologies Used**

* C++
* Object-Oriented Programming (OOP)
* Data Structures

  * Binary Tree
  * Priority Queue (Min Heap)
  * Hash Map

**How to Run**

1. Clone the repository:

2. Open the project in your preferred C++ IDE or compiler.

3. Compile the source files:

   ```
   g++ main.cpp HuffmanEncoder.cpp -o HuffmanEncoder
   ```

4. Run the program:

   ```
   ./HuffmanEncoder
   ```

5. Enter the required input or modify `input.txt` as needed.

**Output Files**

* compressed_bits.txt – Stores the compressed binary data.
* output_decompressed.txt – Stores the decompressed text.
* huffman_report.txt – Contains the Huffman codes and character frequencies.


**Documentation**

* DSA Project Report.pdf – Complete project report.
* Flowchart.png – Flowchart illustrating the algorithm.


**Learning Outcomes**

This project demonstrates:

* Huffman Tree Construction
* Greedy Algorithms
* File Handling in C++
* Priority Queue Implementation
* Binary Tree Traversal
* Data Compression Techniques

**Author:**
Aroona Noor

BS Computer Science

Bahria University




