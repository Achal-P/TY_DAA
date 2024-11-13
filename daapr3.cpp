/*develop a program to implement Huffam Encoding using greedy method*/
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

// A node of the Huffman tree
struct Node {
    char ch;  // Character
    int freq; // Frequency of the character
    Node *left, *right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// Compare function for priority queue (min-heap)
struct compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq; // Min-heap based on frequency
    }
};

// Recursive function to generate the Huffman codes
void generateHuffmanCodes(Node* root, string str, unordered_map<char, string>& huffmanCodes) {
    if (!root) {
        return;
    }

    // If it's a leaf node, assign the code to the character
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = str;
    }

    generateHuffmanCodes(root->left, str + "0", huffmanCodes);
    generateHuffmanCodes(root->right, str + "1", huffmanCodes);
}

// Function to print the Huffman Tree in a readable format
void printHuffmanTree(Node* root, string indent = "", bool isLeft = true) {
    if (root != nullptr) {
        cout << indent;
        if (isLeft) {
            cout << "L----";
            indent += "     ";
        } else {
            cout << "R----";
            indent += "|    ";
        }

        if (root->ch != '\0') {
            cout << "(" << root->ch << ": " << root->freq << ")" << endl;
        } else {
            cout << "(internal: " << root->freq << ")" << endl;
        }

        printHuffmanTree(root->left, indent, true);
        printHuffmanTree(root->right, indent, false);
    }
}

// Function to implement Huffman coding
void huffmanCoding(const unordered_map<char, int>& frequencies) {
    // Create a priority queue (min-heap)
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    // Create leaf nodes for each character and add to the heap
    for (auto pair : frequencies) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Build the Huffman tree
    while (minHeap.size() != 1) {
        // Extract the two nodes with the smallest frequency
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with the sum of the frequencies
        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        // Add the new node to the heap
        minHeap.push(newNode);
    }

    // Root of the Huffman tree
    Node* root = minHeap.top();

    // Generate the Huffman codes by traversing the tree
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Print the Huffman codes
    cout << "\nHuffman Codes:" << endl;
    for (auto pair : huffmanCodes) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // Print the Huffman Tree
    cout << "\nHuffman Tree Structure:" << endl;
    printHuffmanTree(root);
}

int main() {
    // Input: characters and their frequencies
    unordered_map<char, int> frequencies;
    int n;
    cout << "Enter the number of characters: ";
    cin >> n;
    cout << "Enter characters and their frequencies:" << endl;
    for (int i = 0; i < n; i++) {
        char ch;
        int freq;
        cin >> ch >> freq;
        frequencies[ch] = freq;
    }

    // Perform Huffman coding
    huffmanCoding(frequencies);

    return 0;
}
/*output:
Enter the number of characters: 8
Enter characters and their frequencies:
z 2
k 7
m 24
c 32
d 42
l 42
e 120
u 37

Huffman Codes:
k : 111101
m : 11111
z : 111100
c : 1110
d : 110
l : 101
u : 100
e : 0

Huffman Tree Structure:
L----(internal: 306)
     L----(e: 120)
     R----(internal: 186)
     |    L----(internal: 79)
     |         L----(u: 37)
     |         R----(l: 42)
     |    R----(internal: 107)
     |    |    L----(d: 42)
     |    |    R----(internal: 65)
     |    |    |    L----(c: 32)
     |    |    |    R----(internal: 33)
     |    |    |    |    L----(internal: 9)
     |    |    |    |         L----(z: 2)
     |    |    |    |         R----(k: 7)
     |    |    |    |    R----(m: 24) */
