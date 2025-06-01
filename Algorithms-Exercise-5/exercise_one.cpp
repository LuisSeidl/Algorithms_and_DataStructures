// C++ Program for Implementing Binary Tree
#include <iostream>
#include <queue>
#include <cmath>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// Template class for the Node of a Binary Tree
template <typename T>
class Node {
public:
    // Data held by the node
    T data;  
    // Pointer to the left child
    Node* left;  
    // Pointer to the right child
    Node* right;  

    // Constructor to initialize the node with a value
    Node(T value) : data(value), left(nullptr), right(nullptr) {}

    bool contains(T value){
        if (this->data == value) return true;
        else if (value < this->data && this->left != nullptr) return left->contains(value);
        else if (value > this->data && this->right != nullptr) return right->contains(value);
        else return false;
    }


    void insert(Node<T>* newNode){
        if (newNode->data <= this->data){
            if (this->left == nullptr) this->left = newNode;
            else this->left->insert(newNode);
        }
        else{
            if (this->right == nullptr) this->right = newNode;
            else this->right->insert(newNode);
        }
    }

    //helper function that gets the max height from the desired node
    int getHeight() {
        int leftHeight = (left == nullptr) ? 0 : left->getHeight();
        int rightHeight = (right == nullptr) ? 0 : right->getHeight();
        return 1 + std::max(leftHeight, rightHeight);
    }
};

// Template class for a Binary Tree
template <typename T>
class BinaryTree {
private:
    // Pointer to the root of the tree
    Node<T>* root;  


    // Recursive Function to delete a node from the tree
    Node<T>* deleteRecursive(Node<T>* current, T value) {
        if (current == nullptr) return nullptr;

        if (current->data == value) {
            if (current->left == nullptr && current->right == nullptr) {
                delete current;
                return nullptr;
            }
            if (current->left == nullptr) {
                Node<T>* temp = current->right;
                delete current;
                return temp;
            }
            if (current->right == nullptr) {
                Node<T>* temp = current->left;
                delete current;
                return temp;
            }

            Node<T>* successor = findMin(current->right);
            current->data = successor->data;
            current->right = deleteRecursive(current->right, successor->data);
        } else {
            current->left = deleteRecursive(current->left, value);
            current->right = deleteRecursive(current->right, value);
        }
        return current;
    }

    // Helper Function to find the minimum value node
    Node<T>* findMin(Node<T>* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    // Recursive Function to search for a value in the tree
    bool searchRecursive(Node<T>* current, T value) {
        if (current == nullptr) return false;
        if (current->data == value) return true;
        return searchRecursive(current->left, value) || searchRecursive(current->right, value);
    }

    // Function for Recursive inorder traversal of the tree
    void inorderRecursive(Node<T>* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            cout << node->data << " ";
            inorderRecursive(node->right);
        }
    }

    // Function for Recursive preorder traversal of the tree
    void preorderRecursive(Node<T>* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorderRecursive(node->left);
            preorderRecursive(node->right);
        }
    }

    // Function for Recursive postorder traversal of the tree
    void postorderRecursive(Node<T>* node) {
        if (node != nullptr) {
            postorderRecursive(node->left);
            postorderRecursive(node->right);
            cout << node->data << " ";
        }
    }

public:
    // Constructor to initialize the tree
    BinaryTree() : root(nullptr) {}

    // Function to insert a node in the binary tree 
    void insertNode(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        queue<Node<T>*> q;
        q.push(root);

        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();

            if (current->left == nullptr) {
                current->left = newNode;
                return;
            } else {
                q.push(current->left);
            }

            if (current->right == nullptr) {
                current->right = newNode;
                return;
            } else {
                q.push(current->right);
            }
        }
    }

    // Function to delete a node from the tree
    void deleteNode(T value) {
        root = deleteRecursive(root, value);
    }

    // Function to search for a value in the tree
    bool search(T value) {
        return searchRecursive(root, value);
    }

    // Function to perform inorder traversal of the tree
    void inorder() {
        inorderRecursive(root);
        cout << endl;
    }

    // Function to perform preorder traversal of the tree
    void preorder() {
        preorderRecursive(root);
        cout << endl;
    }

    // Function to perform postorder traversal of the tree
    void postorder() {
        postorderRecursive(root);
        cout << endl;
    }

    // Function  to perform level order traversal of the tree
    void levelOrder() {
        if (root == nullptr) return;

        queue<Node<T>*> q;
        q.push(root);

        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
        cout << endl;
    }

    bool contains(T value){
        Node<T>* current = root;
        
        while(current != nullptr){
            if (current->data == value) return true;
            if (value < current->data) current = current->left;
            else current = current->right;
        }
        return false;
    }

    
    //insertion like a Binary Search tree
    void BST_insert(T value){
        Node<T>* newNode = new Node<T>(value);

        //if BST is empty we setup our tree and return
        if (root == nullptr) {
            root = newNode;
            return;
        }
        //if not we insert the value
        else root->insert(newNode);
    }


    //now trying to make a pretty output function
    void prettyTree() {
        if (root == nullptr) return;

        int height = root->getHeight();
        int maxWidth = pow(2, height) * 2;

        vector<Node<T>*> currentLevel;
        currentLevel.push_back(root);

        for (int depth = 0; depth < height; ++depth) {
            vector<Node<T>*> nextLevel;

            int spacesBefore = maxWidth / pow(2, depth + 1); // spacing before the first element
            int spacesBetween = maxWidth / pow(2, depth);    // spacing between elements

            // print leading spaces
            printSpaces(spacesBefore);

            // print node values
            for (Node<T>* node : currentLevel) {
                if (node) {
                    cout << node->data;
                    nextLevel.push_back(node->left);
                    nextLevel.push_back(node->right);
                } else {
                    cout << " ";
                    nextLevel.push_back(nullptr);
                    nextLevel.push_back(nullptr);
                }
                printSpaces(spacesBetween - 1); // space between nodes
            }

            cout << endl;

            // Print branches (/ and \)
            if (depth < height - 1) {
                printBranches(currentLevel, spacesBefore, spacesBetween);
            }

            currentLevel = nextLevel;
        }

        cout << endl;
    }

    // Helper: prints spaces
    void printSpaces(int count) {
        for (int i = 0; i < count; ++i) {
            cout << " ";
        }
    }

    // Helper: prints connecting lines between nodes
    void printBranches(vector<Node<T>*>& level, int spacesBefore, int spacesBetween) {
        int items = level.size();
        printSpaces(spacesBefore - 1);

        for (int i = 0; i < items; ++i) {
            if (level[i]) {
                if (level[i]->left) cout << "/";
                else cout << " ";

                printSpaces(1);

                if (level[i]->right) cout << "\\";
                else cout << " ";
            } else {
                cout << "   ";
            }

            printSpaces(spacesBetween - 3); // spacing after branches
        }

        cout << endl;
    }


    void preOrderInput(){
        if(this->root != nullptr) {
            cout << "Tree already exists, can't enter new Values using this Input";
        } else{
            cout << endl << "Input the desired Tree in Preorder Structure" << endl;
            string input;
            cin >> input;

            string cleanedInput;

            for(char c : input){
                if(isdigit(c) || c == ',') cleanedInput += c;
            }

            stringstream ss(cleanedInput);
            string segment;
            vector<string> nodes;

            while(getline(ss, segment, ',')){
                nodes.push_back(segment);
            }

            nodes.erase(
                remove_if(nodes.begin(), nodes.end(),
                        [](const string& s) { return s.empty(); }),
                nodes.end());

            
            
            if (this->root != nullptr) {
                cout << "Tree already exists, can't enter new values from preOrderInput";
            }

            for(const string& s : nodes){
                this->BST_insert(stoi(s));
            }
        }
    }   

};

int main() {
    BinaryTree<int> tree;
    
    // Insert the nodes into the tree
    /*
    int arr [6] = {6, 3, 8, 1, 7, 9};

    for(int a : arr){
        tree.BST_insert(a);
    }

    

    cout << "Inorder traversal: ";
    tree.inorder();

    cout << "Preorder traversal: ";
    tree.preorder();

    cout << "Postorder traversal: "; 
    tree.postorder();

    cout << "Level order traversal: ";
    tree.levelOrder();

    cout << "Searching for 7: " << (tree.search(7) ? "Found" : "Not Found") << endl;
    cout << "Searching for 6: " << (tree.search(6) ? "Found" : "Not Found") << endl;

    cout << "Does 3 exist in our Tree? " << (tree.contains(3) ? "Yes" : "No") << endl;
    */

    tree.preOrderInput();

    cout << "Pretty Tree graphics: " << endl << endl;
    tree.prettyTree();
    return 0;
}