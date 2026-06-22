#include "HuffmanEncoder.h"
#include <iostream>

using namespace std;

const string ORIGINAL_FILE = "input.txt";
const string COMPRESSED_BITS_FILE = "compressed_bits.txt";
const string DECOMPRESSED_FILE = "output_decompressed.txt";
const string REPORT_FILE = "huffman_report.txt";

void displayMenu() {
    cout << "\n=========================================\n";
    cout << "  HUFFMAN ENCODING COMPRESSION \n";
    cout << "=========================================\n";
    cout << "1. Run Full Compression/Decompression Cycle\n";
    cout << "2. Exit\n";
    cout << "Enter choice: ";
}

int main() {

    HuffmanEncoder encoder;
    int choice = 0;

    do {
        displayMenu();
        if (!(cin >> choice)) {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');  // discards up to 10000 characters or until a newline is found 
            continue;
        }

        switch (choice) {
        case 1: {
            cout << "\n--- STARTING FULL HUFFMAN CYCLE ---\n";

            // opens report file for logging all results
            ofstream reportFile(REPORT_FILE);

            // --- Task 1: read input text ---
            string originalText = readFile("input.txt");

            if (originalText.empty()) {
                cout << "Error: Could not read original text from input.txt. \n";
                cout << "Please ensure input.txt exists and contains text.\n";
                reportFile << "Error: Could not read original text. Cycle stopped.\n";
                reportFile.close();
                break;
            }
            cout << "Original Text (Length " << originalText.length() << "): '" << originalText << "'\n";

            // --- Task 5: encode text ---
            //(includes frequency count, tree build, and code generation)
            string encodedBitString = encoder.encode(originalText);
            int compressedLength = encodedBitString.length();
            cout << "Encoding successful. Compressed length: " << compressedLength << " bits.\n";

            // --- Task 6: write encoded output to file ---
            writeFile(COMPRESSED_BITS_FILE, encodedBitString);
            cout << "Encoded bit stream written to: " << COMPRESSED_BITS_FILE << endl;

            // --- to display results to console and file ---

            encoder.displayTree(cout);
            encoder.displayTree(reportFile);

            encoder.displayFrequencies(cout);
            encoder.displayFrequencies(reportFile);

            encoder.displayCodes(cout);
            encoder.displayCodes(reportFile);

            // --- Task 7: decode using huffman tree ---
            string decodedText = encoder.decode(encodedBitString);
            cout << "\nDecoding successful.\n";
            cout << "Decoded Text (Length " << decodedText.length() << "): '" << decodedText << "'\n";

            writeFile(DECOMPRESSED_FILE, decodedText);
            cout << "Decompressed text written to: " << DECOMPRESSED_FILE << endl;

            cout << "\n--- Verification and Statistics ---\n";

            if (originalText == decodedText) {
                cout << "VERIFICATION SUCCESSFUL: Lossless compression confirmed.\n";
            }
            else {
                cout << "VERIFICATION FAILED: Data mismatch after decoding.\n";
            }

            // --- Task 8: display compression statistics ---
            encoder.displayStats(cout, originalText.length(), compressedLength);
            encoder.displayStats(reportFile, originalText.length(), compressedLength);

            reportFile.close();
            cout << "Full report log written to: " << REPORT_FILE << endl;

            break;
        }
        case 2:
            cout << "\nExiting Huffman Encoder .\n";
            break;
        default:
            cout << "\nInvalid choice. Please select 1 or 2.\n";
            break;
        }
    } while (choice != 2);

    return 0;
}