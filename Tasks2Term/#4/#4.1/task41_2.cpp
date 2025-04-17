#include <iostream>
#include <string>
#include <vector>

using namespace std;

// структура дерева
struct Tree {
    int inf;
    Tree* left, * right;
    Tree* parent;

    Tree(int val) : inf(val), left(nullptr), right(nullptr), parent(nullptr) {}

};

// вставка нового элемента в дерево
void insert(Tree*& tr, int val) {
    Tree* p = new Tree(val);
    if(!tr) tr = p;
    else if(val > tr->inf) {
        if (tr->right) {
            insert(tr->right, val);
        }
        else {
            tr->right = p;
            tr->right->parent = tr;
        }
    }
    else if(val < tr->inf){
        if (tr->left) {
            insert(tr->left, val);
        }
        else {
            tr->left = p;
            tr->left->parent = tr;
        }
    }
}

// считать строку и создать дерево
Tree* createTree() {
    string str;
    Tree* tr = NULL;
    cout << "Enter sequence: ";
    getline(cin, str);
    str += ' ';
    while(str != "") {
        string buf = str.substr(0, str.find_first_of(' '));
        insert(tr, stoi(buf));
        str.erase(str.begin(), str.begin() + str.find_first_of(' ') + 1);
    }
    return tr;
}

void printVector(vector<int> v) {
    for(int num: v) cout << num << ' ';
}

// найти узлы с одним ребёнком
void inorder(Tree* tr) {
    if(tr) {
        inorder(tr->left);
        if((!tr->left && tr->right) || (tr->left && !tr->right)) cout << tr->inf << ' ';
        inorder(tr->right);
    }
}

int main() {

    // 10, 5, 15, 4, 13
    Tree* tr = createTree();

    cout << "Nodes with one children: ";
    inorder(tr);
    cout << endl;

    system("pause");
    return 0;

}