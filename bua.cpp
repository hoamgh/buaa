#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include<math.h>
using namespace std;

struct pokemon {
    string Name;
    string Type1, Type2;
    vector<string> Abi;
    int HP, Atk, Def, SpAtk, SpDef, Spd;
    vector<string> nextEv;
    vector<string> Moves;
};

struct BSTNode {
    pokemon data;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* newNode(pokemon pkm) {
    BSTNode* temp = new BSTNode;
    temp->data = pkm;
    temp->left = temp->right = nullptr;
    return temp;
}

BSTNode* insert(BSTNode* node, pokemon pkm) {
    if (node == nullptr) return newNode(pkm);
    int x=pkm.nextEv.size();
    if (x < node->data.nextEv.size())
        node->left = insert(node->left, pkm);

    else if(x==node->data.nextEv.size()){
        if(pkm.Name<node->data.Name){
            node->left = insert(node->left, pkm);
        }
        if(pkm.Name>node->data.Name){
            node->right = insert(node->right, pkm);
        }
    }
    else
        node->right = insert(node->right, pkm);

    return node;
}
void NLR(BSTNode* pRoot) {
    if (pRoot != nullptr) {
        cout << pRoot->data.Name << " ";
        NLR(pRoot->left);
        NLR(pRoot->right);
    }
}
void LNR(BSTNode* pRoot) {
    if (pRoot != nullptr) {
        LNR(pRoot->left);
        cout << pRoot->data.Name << " ";
        LNR(pRoot->right);
    }
}
void LRN(BSTNode* pRoot) {
    if (pRoot != nullptr) {
        LRN(pRoot->left);
        LRN(pRoot->right);
        cout << pRoot->data.Name << " ";
    }
}
// 7. Calculate the height of a given Binary Tree
int Height(BSTNode* pRoot) {
    if (pRoot == nullptr) return -1;
    int leftHeight = Height(pRoot->left);
    int rightHeight = Height(pRoot->right);
    return 1 + max(leftHeight, rightHeight);
}

// 8. Count the number of NODE from a given Binary Tree
int countNode(BSTNode* pRoot) {
    if (pRoot == nullptr) return 0;
    return 1 + countNode(pRoot->left) + countNode(pRoot->right);
}
// 9. Calculate the total value of all NODEs from a given Binary Tree
// Assuming 'value' is an integer property of pokemon. Adjust accordingly.
int sumNode(BSTNode* pRoot) {
    if (pRoot == nullptr) return 0;
    return pRoot->data.HP + sumNode(pRoot->left) + sumNode(pRoot->right); // Example using HP as value
}
// Remove the duplicate definition of countLeaf function
// 10. Find and return a NODE with given value from a given Binary Search Tree
// Assuming we search by Name which is a string. Adjust if searching by another property.
BSTNode* Search(BSTNode* pRoot, string name) {
    if (pRoot == nullptr || pRoot->data.Name == name) return pRoot;
    if (name < pRoot->data.Name) return Search(pRoot->left, name);
    else return Search(pRoot->right, name);
}
void LevelOrder(BSTNode* pRoot) {
    if (!pRoot) return;
    queue<BSTNode*> q;
    q.push(pRoot);
    while (!q.empty()) {
        BSTNode* current = q.front();
        q.pop();
        cout << current->data.Name << " ";
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}
// 13. Completely remove a given Binary Search Tree
void removeTree(BSTNode* &pRoot) {
    if (pRoot != nullptr) {
        removeTree(pRoot->left);
        removeTree(pRoot->right);
        delete pRoot;
        pRoot = nullptr;
    }
}
// Remove the duplicate definition of countLeaf function
// 16. Count the number leaves from a given Binary Tree
int countLeaf(BSTNode* pRoot) {
    if (pRoot == nullptr) return 0;
    if (pRoot->left == nullptr && pRoot->right == nullptr) return 1;
    if (pRoot->left==nullptr) return countLeaf(pRoot->right);
    if (pRoot->right==nullptr) return countLeaf(pRoot->left);
    return countLeaf(pRoot->left) + countLeaf(pRoot->right);
}
// 17. Count the number of NODE from a given Binary Search Tree which key value is less than a given value
// Assuming comparison by Name. Adjust accordingly for other properties.
int countLess(BSTNode* pRoot, string name) {
    if (pRoot == nullptr) return 0;
    int count = (pRoot->data.Name < name) ? 1 : 0;
    return count + countLess(pRoot->left, name) + countLess(pRoot->right, name);
}
// 18. Count the number of NODE from a given Binary Search Tree which key value is greater than a given value
int countGreater(BSTNode* pRoot, string name) {
    if (pRoot == nullptr) return 0;
    int count = (pRoot->data.Name > name) ? 1 : 0;
    return count + countGreater(pRoot->left, name) + countGreater(pRoot->right, name);
}
void Remove(BSTNode*& pRoot, int HP) {
    if (pRoot == nullptr) return; // Base case: The tree is empty or the node is not found.

    if (HP < pRoot->data.HP) {
        // If the HP to be deleted is less than the root node's HP, then it lies in left subtree
        Remove(pRoot->left, HP);
    } else if (HP > pRoot->data.HP) {
        // If the HP to be deleted is greater than the root node's HP, then it lies in right subtree
        Remove(pRoot->right, HP);
    } else {
        // If the HP is the same as the root's HP, then this is the node to be deleted
        // Node with only one child or no child
        if (pRoot->left == nullptr) {
            BSTNode* temp = pRoot->right;
            delete pRoot;
            pRoot = temp;
        } else if (pRoot->right == nullptr) {
            BSTNode* temp = pRoot->left;
            delete pRoot;
            pRoot = temp;
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            BSTNode* temp = pRoot->right;
            while (temp && temp->left != nullptr) temp = temp->left;

            // Copy the inorder successor's content to this node
            pRoot->data = temp->data;

            // Delete the inorder successor
            Remove(pRoot->right, temp->data.HP);
        }
    }
}
bool isBSTInOrder(BSTNode* pRoot, int &x){
	if (pRoot == NULL) return true;
	if (!isBSTInOrder(pRoot->left, x)) return false;
	if (pRoot->data.HP <= x) return false;
	x = pRoot->data.HP;
	return isBSTInOrder(pRoot->right, x);
}
int Level(BSTNode* pRoot, BSTNode* p) {
    if (pRoot == nullptr) {
        return -1; // Node not found
    }

    // If the node is found
    if (pRoot == p) {
        return 1; // Level is 0 (or 1 if you count the root level as 1)
    }

    // Search in the left or right subtree
    int level = max(Level(pRoot->left, p), Level(pRoot->right, p));

    // If the node was found in the left or right subtree, add 1 to the level
    if (level != -1) {
        return level + 1;
    }

    // If the node is not found in both subtrees
    return -1;
}
BSTNode* createTree(vector<pokemon> p) {
    BSTNode* root = nullptr;
    for (auto& pokemon : p) {
        root = insert(root, pokemon);
    }
    return root;
}
int heightNode(BSTNode* pRoot, int HP) {
    // Base case: The tree is empty or the node is not found
    if (pRoot == nullptr) {
        return -1; // Node not found or tree is empty
    }

    // If the HP is less than the current node's HP, search in the left subtree
    if (HP < pRoot->data.HP) {
        return heightNode(pRoot->left, HP);
    }
    // If the HP is greater than the current node's HP, search in the right subtree
    else if (HP > pRoot->data.HP) {
        return heightNode(pRoot->right, HP);
    }
    // If the HP matches the current node's HP, calculate the height of this node
    else {
        return Height(pRoot);
    }
}

bool isPerfectBST(BSTNode* root) {
    if (root == nullptr) return true;
    int nodeCount = countNode(root);
    int height = Height(root);

    // Tính 2^height và trừ đi 1, sau đó so sánh với số lượng nút
    return static_cast<int>(pow(2, height)) - 1 == nodeCount;
}
bool isFullBST(BSTNode* pRoot) {
    // Base case: An empty tree is a full BST
    if (pRoot == nullptr) {
        return true;
    }

    // Check if both children are absent
    if (pRoot->left == nullptr && pRoot->right == nullptr) {
        return true;
    }

    // Check if both children are present
    if (pRoot->left != nullptr && pRoot->right != nullptr) {
        // Recursively check the subtrees
        return isFullBST(pRoot->left) && isFullBST(pRoot->right);
    }

    // If one child is present and the other is absent, it's not a full BST
    return false;
}
void inorder(BSTNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data.nextEv.size() << " ";
        cout << root->data.Name<<" "<<endl;
        inorder(root->right);
    }
}
int Stoi(const string& str) {
    int num = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ') {
        i++;
    }

    if (str[i] == '-' || str[i] == '+') {
        sign = (str[i] == '-') ? -1 : 1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        num = num * 10 + (str[i] - '0');
        i++;
    }

    return num * sign;
}

string layChuoi(string temp) {
    string a = "";
    int n= temp.size();
    for (int i = 0;i < n; i++) {
        if (isalpha(temp[i]) || temp[i] == ';' || ((temp[i] == ' ') && isalpha(temp[i - 1]) && isalpha(temp[i + 1]))) {
            a += temp[i];
        }
    }
    return a;
}

pokemon readPokemon(string line_info) {
    pokemon res;
    stringstream ss(line_info);
    getline(ss, res.Name, ',');

    string temp, hpStr;
    getline(ss, temp, ',');
    stringstream e(layChuoi(temp));
    getline(e, res.Type1, ';');
    getline(e, res.Type2, ';');
    getline(ss, temp, ',');
    stringstream b(layChuoi(temp));
    while (getline(b, temp, ';')) {
        res.Abi.push_back(temp);
    }

    getline(ss, hpStr, ',');
    res.HP = Stoi(hpStr);
    getline(ss, temp, ',');
    res.Atk = Stoi(temp);
    getline(ss, temp, ',');
    res.Def = Stoi(temp);
    getline(ss, temp, ',');
    res.SpAtk = Stoi(temp);
    getline(ss, temp, ',');
    res.SpDef = Stoi(temp);
    getline(ss, temp, ',');
    res.Spd = Stoi(temp);

    getline(ss, temp, ',');
    stringstream f(layChuoi(temp));
    while (getline(f, temp, ';')) {
        res.nextEv.push_back(temp);
    }

    if (getline(ss, temp)) {
        stringstream g(layChuoi(temp));
        while (getline(g, temp, ';')) {
            res.Moves.push_back(temp);
        }
    }
    return res;
}
BSTNode* readBST(const string& filename) {
    fstream fs;
    fs.open(filename);
    BSTNode* res = nullptr;
    if (fs.is_open()) {
        string line = "";
        getline(fs, line);
        while (getline(fs, line)) {
            pokemon temp = readPokemon(line);
            res = insert(res, temp);
        }
        fs.close();
    } else {
        cout << "Cannot open file" << endl;
    }

    return res;
}
bool dieuKien(pokemon temp){
    if(temp.HP>89) return true;
    return false;
}
vector<pokemon> readFileVector(string filename){
    fstream fs(filename);
    vector<pokemon> res;
    if(!fs.is_open()){
        return res;
    }
    string line="";
    getline(fs,line);
    while (getline(fs,line))    
    {   
        pokemon temp=readPokemon(line);
        if(dieuKien(temp)) res.push_back(temp);
    }
    return res;
    
} 
pokemon*** readFile(const string& filename, int m, int n, int p) {
    fstream fs(filename);
    if (!fs.is_open()) {
        return nullptr;
    }
    string line = "";
    getline(fs, line);

    pokemon*** poke = new pokemon**[m];
    for (int i = 0; i < m; i++) {
        poke[i] = new pokemon*[n];
        for (int j = 0; j < n; j++) {
            poke[i][j] = new pokemon[p];
            for (int k = 0; k < p; k++) {
                if (getline(fs, line)) {
                    poke[i][j][k] = readPokemon(line);
                }
            }
        }
    }

    fs.close();
    return poke;
}
int countSubtree(BSTNode *root){
    // Kiểm tra nếu root là nullptr hoặc là nút lá
    if(root == nullptr || (root->left == nullptr && root->right == nullptr)) return 0;
    
    int Trai = sumNode(root->left);
    int Phai = sumNode(root->right);
    
    // Kiểm tra điều kiện trước khi so sánh để tránh truy cập vào nullptr
    if(root->left != nullptr && root->right != nullptr && Phai > (2 * Trai)){
        return 1+countSubtree(root->left)+countSubtree(root->right);
    }
    else return countSubtree(root->left)+countSubtree(root->right);
}


int main() {
    string filename = "pokemon.csv";
    BSTNode*p=readBST(filename);
    inorder(p);
    return 0;
}