#include<bits/stdc++.h>
using namespace std;

// Định nghĩa cấu trúc Node cho cây Huffman
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}

    // Hàm tạo một node mới từ hai node đã có
    Node(Node* left, Node* right) : data('\0'), freq(left->freq + right->freq), left(left), right(right) {}
};

// So sánh ưu tiên dựa trên tần suất của các node
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Hàm xây dựng cây Huffman từ bảng ký tự và tần suất
Node* buildHuffmanTree(map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Thêm các node lá vào hàng đợi ưu tiên
    for (auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Xây dựng cây Huffman
    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* combined = new Node(left, right);
        pq.push(combined);
    }

    return pq.top();
}

// Hàm duyệt cây Huffman và tạo mã Huffman cho từng ký tự
void generateHuffmanCodes(Node* root, string code, map<char, string>& huffmanCodes) {
    if (root == nullptr) return;

    // Nếu là node lá, lưu mã Huffman của nó vào bảng mã
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }

    // Duyệt qua cây để tạo mã Huffman
    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

int main() {
    string input = "Huffman coding";
    map<char, int> freqMap;

    // Tính tần suất của các ký tự trong input
    for (char c : input) {
        freqMap[c]++;
    }

    // Xây dựng cây Huffman từ bảng tần suất
    Node* root = buildHuffmanTree(freqMap);

    // Tạo mã Huffman cho từng ký tự
    map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // In ra mã Huffman của các ký tự
    cout << "Huffman Codes:" << endl;
    for (auto& pair : huffmanCodes) {
        cout << pair.first << " : " << pair.second << endl;
    }

    return 0;
}
