// Create a Sorting algorithm using AVL trees

//Idea: Insertion into the Tree and then once the tree is built (a normal BST Tree would be enough), we get the Values using InOrder Traversal which outputs the Sorted Array (Ascending)

#include <bits/stdc++.h> 
using namespace std;

class Node {
public:
    int data;  
    Node* left;  
    Node* right;  
    int height;

    Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}

    bool contains(int value){
        if (this->data == value) return true;
        else if (value < this->data && this->left != nullptr) return left->contains(value);
        else if (value > this->data && this->right != nullptr) return right->contains(value);
        else return false;
    }
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

    void inorderRecursive(Node* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            cout << node->data << " ";
            inorderRecursive(node->right);
        }
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

    //Helper function for the deleteNode function
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



    int main(){
        Node *root = nullptr;

        vector<int> values = {5, 6, 9, 12, 13, 3, 8, 10, 11, 16,15, 14, 7, 4, 2, 1};

        for(int i : values){
            root = insert(root, i);
        }

        cout << "Inorder traversal of the "
                "constructed AVL tree is \n";
        inorderRecursive(root);


        vector<int> valuesToDelete = {12, 8, 5, 4, 3, 6, 15, 14};

        for(int i : valuesToDelete){
        root = deleteNode(root, i);
        }

        cout << "\nInorder traversal after deletion \n";
        inorderRecursive(root);

        return 0;
    }