#include <bits/stdc++.h> 
using namespace std;

// class for the Node of a Binary Tree
class Node {
public:
    // Data held by the node
    int data;  
    // Pointer to the left child
    Node* left;  
    // Pointer to the right child
    Node* right;  
    // Height of the Node
    int height;

    // Constructor to initialize the node with a value and height
    Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}

    // recursive function that searches through the Tree if the value is in there
    bool contains(int value){
        if (this->data == value) return true;
        else if (value < this->data && this->left != nullptr) return left->contains(value);
        else if (value > this->data && this->right != nullptr) return right->contains(value);
        else return false;
    }

    // insertion of a 
    void insert(Node* newNode){
        if (newNode->data <= this->data){
            if (this->left == nullptr) this->left = newNode;
            else this->left->insert(newNode);
        }
        else{
            if (this->right == nullptr) this->right = newNode;
            else this->right->insert(newNode);
        }
    }


};

    int getHeight(Node *N){
        if (N == nullptr) return 0;
        return N->height;
    }


    Node *rightRotate(Node *y){
        Node *x = y->left;
        Node *T2 = x->right;

        //Rotation
        x->right = y;
        y->left = T2;

        //update Heights
        y->height = 1+max(getHeight(y->left), getHeight(y->right));
        x->height = 1+max(getHeight(x->left),getHeight(x->right));

        //return new root
        return x;
    }


    Node *leftRotate(Node *x){
        Node *y = x->right;
        Node *T2 = y->left;

        //Rotation
        y->left = x;
        x->right = T2;

        //update Heights
        x->height = 1+max(getHeight(x->left),getHeight(x->right));
        y->height = 1+max(getHeight(y->left),getHeight(y->right));

        //return new root
        return y;
    }


    int getBalance(Node *N){
        if(N == nullptr) return 0;
        return getHeight(N->left)-getHeight(N->right);
    }


    Node* insert(Node* node, int key){

        //normal BST insertion
        if(node == nullptr) return new Node(key);

        if(key < node->data){
            node->left = insert(node->left, key);
        }
        else if(key > node->data){
            node->right = insert(node->right, key);
        }
        else return node;

        //update height of ancerstor node
        node->height = 1+max(getHeight(node->left),getHeight(node->right));

        int balance = getBalance(node);

        //if the node is unbalanced, there are 4 cases

        //Left Left Case
        if(balance > 1 && key < node->left->data) return rightRotate(node);

        //Right Right Case
        if(balance < -1 && key > node->right->data) return leftRotate(node);

        //Left Right Case
        if(balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //Right Left Case
        if(balance < -1 && key < node->right->data){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        //return the unchanged node pointer
        return node;
    }


    Node* minValueNode(Node* node){
        Node* current = node;

        while(current->left != nullptr)
            current = current->left;

        return current;
    }


    Node* deleteNode(Node* root, int key){

        //1. Standard BST delete
        if(root == nullptr)
            return root;

        //if the deleted key is smaller than the roots key, it is in the left subtree
        if(key < root->data)
            root->left = deleteNode(root->left, key);

        //if it is bigger, it has to be in the right subtree
        else if(key > root->data)
            root->right = deleteNode(root->right, key);

        // if it is the same as this nodes key, this node has to be deleted
        else{
            if((root->left == nullptr) || (root->right == nullptr)){
                Node* temp = root->left ? root->left : root->right;

                //No child case
                if(temp == nullptr){
                    temp = root;
                    root = nullptr;
                } //One Child Case
                else {
                    *root = *temp; //copy the Contents of the non empty child
                    free(temp);
                }
            } else{
                //Node with two Children

                //get the inorder Successor (smallest from the bigger nodes)
                Node* temp = minValueNode(root->right);

                root->data = temp->data;

                //delete the successor

                root->right = deleteNode(root->right, temp->data);
            }
        }
        //If the Tree had only one node then return

        if(root == nullptr)
            return root;

        //2. Update Height

        root->height = 1+max(getHeight(root->left),getHeight(root->right));

        //3. Get Balance to check if we now are unbalanced
        int balance = getBalance(root);

        //If unbalanced, there are 4 cases

        //Left Left Case
        if(balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);

        //Right Right Case
        if(balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);

        //Left Right Case
        if(balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        //Right Left Case
        if(balance < -1 && getBalance(root->right) > 0){
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }


    void preOrder(Node* root){
        if (root != nullptr){
            cout << root->data << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }


    // Helper: prints spaces
    void printSpaces(int count) {
        for (int i = 0; i < count; ++i) {
            cout << " ";
        }
    }

    // Helper: prints connecting lines between nodes
    void printBranches(vector<Node*>& level, int spacesBefore, int spacesBetween) {
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


    void prettyTree(Node* root) {
        if (root == nullptr) return;

        int height = getHeight(root);
        int maxWidth = pow(2, height) * 2;

        vector<Node*> currentLevel;
        currentLevel.push_back(root);

        for (int depth = 0; depth < height; ++depth) {
            vector<Node*> nextLevel;

            int spacesBefore = maxWidth / pow(2, depth + 1); // spacing before the first element
            int spacesBetween = maxWidth / pow(2, depth);    // spacing between elements

            // print leading spaces
            printSpaces(spacesBefore);

            // print node values
            for (Node* node : currentLevel) {
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

   


    int main(){
        Node *root = nullptr;

        vector<int> nodes = {5, 6, 9, 12, 13, 3, 8, 10, 11, 16,15, 14, 7, 4, 2, 1};

        for(int node : nodes){
            root = insert(root, node);
        }

        cout << "Preorder traversal of the "
                "constructed AVL tree is: ";
        preOrder(root);

        int treeHeight = getHeight(root) - 1;
        int treeSize = nodes.size();

        cout << "\n Height of the Tree : " << treeHeight  <<" | Elements of the Tree: " << treeSize << endl ;

        cout << "\n Pretty Tree graphics: \n";
        prettyTree(root);

        //vector<int> valuesToDelete = {12, 8, 5, 4, 3, 6, 15, 14};
        //for(int i : valuesToDelete){
        //root = deleteNode(root, i);
        //}
        //cout << "\nPreorder traversal after deletion \n";
        //preOrder(root);
        //cout << "\n Pretty Tree graphics: \n";
        //prettyTree(root);

        return 0;
    }