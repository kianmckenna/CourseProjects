#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class HuffmanTree {
private:
    Node* root;

    Node* buildTree(vector<int>& inOrder, vector<int>& levelOrder) {
        if (inOrder.empty() || levelOrder.empty()) {
            return nullptr;
        }

        int rootVal = levelOrder.front();
        Node* rootNode = new Node(rootVal);
        levelOrder.erase(levelOrder.begin());

        auto i = find(inOrder.begin(), inOrder.end(), rootVal);
        int rootI = distance(inOrder.begin(), i);

        vector<int> leftInOrder(inOrder.begin(), inOrder.begin() + rootI);
        vector<int> rightInOrder(inOrder.begin() + rootI + 1, inOrder.end());
        vector<int> leftLevelOrder, rightLevelOrder;

        for (int val : levelOrder) {
            if (find(leftInOrder.begin(), leftInOrder.end(), val) != leftInOrder.end()) {
                leftLevelOrder.push_back(val);
            } else {
                rightLevelOrder.push_back(val);
            }
        }

        rootNode->left = buildTree(leftInOrder, leftLevelOrder);
        rootNode->right = buildTree(rightInOrder, rightLevelOrder);

        return rootNode;
    }

public:
    HuffmanTree(vector<int>& inOrder, vector<int>& levelOrder) {
        root = buildTree(inOrder, levelOrder);
    }

    void decode(string& text) {
        Node* current = root;
        string decodedText;

        for (char c : text) {
            if (c == '0') {
                current = current->left;
            } else if (c == '1') {
                current = current->right;
            }

            if (current->left == nullptr && current->right == nullptr) {
                decodedText += char(current->data);
                current = root;
            }
        }
        
        cout << decodedText;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: prog.exe inorder_file levelorder_file encoded_file" << endl;
        return 1;
    }

    ifstream inFile1(argv[1]);
    vector<int> inOrder;
    int val;

    while (inFile1 >> val) {
        inOrder.push_back(val);
    }
    inFile1.close();

    ifstream inFile2(argv[2]);
    vector<int> levelOrder;

    while (inFile2 >> val) {
        levelOrder.push_back(val);
    }
    inFile2.close();

    ifstream inFile3(argv[3]);
    string text;
    inFile3.seekg(0, ios::end);
    size_t fileSize = inFile3.tellg();
    text.resize(fileSize);
    inFile3.seekg(0, ios::beg);
    inFile3.read(&text[0], fileSize);
    inFile3.close();

    HuffmanTree huffmanTree(inOrder, levelOrder);

    huffmanTree.decode(text);

    return 0;
}
