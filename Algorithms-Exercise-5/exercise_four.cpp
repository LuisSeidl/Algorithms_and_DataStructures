#include <bits/stdc++.h> 
using namespace std;

class Node {
public:

    // Data held by the node
    int data;  
    // Pointer to the left child
    Node* left;  
    // Pointer to the right child
    Node* right;  

    Node(Node* lp, int value, Node* rp){
        left = lp;
        data = value;
        right = rp;
    }

}; 
    unordered_map<int, int> countCache;

    int countMinAVL(int n){
        if(n==0) return 1;
        else if (n==1) return 2;
        //if( countCache.count(n)) return countCache[n];
        return 2* countMinAVL(n-1) * countMinAVL(n-2);
    }

    vector<Node*> generateMinAVL(int n){
        if (n==0) return {nullptr};
        if (n==1) return {new Node(nullptr, 0, nullptr)};

        vector<Node*> trees;

        vector<pair<int,int>> combinations = {{n-1, n-2}, {n-2, n-1}};

        for (auto [hl,hr] : combinations) {
            auto leftTrees = generateMinAVL(hl);
            auto rightTrees = generateMinAVL(hr);

            for (auto& left : leftTrees){
                for (auto& right : rightTrees){
                    auto root = new Node(left, 0, right);
                    trees.push_back(root);
                }
            }
        }
        return trees;
    }


    int main(){
        int n = 5;

        auto trees = generateMinAVL(n);
        int count = countMinAVL(n);

        cout << "Anzahl minimaler AVL-Bäume der Höhe " << n <<" : " << trees.size() << endl;
        cout << "Zählung (verifiziert): " << count << "\n" << endl;
        return 0;
    }