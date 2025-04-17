#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Tree {
    int inf;
    Tree* left, * right;
    Tree* parent;

    Tree(int val) : inf(val), left(nullptr), right(nullptr), parent(nullptr) {}

};

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

void find(Tree* tr, int x) {
    vector<int> parents;
    while(tr) {
        if(tr->inf == x) return printVector(parents);
        else if(tr->inf < x) {
            parents.push_back(tr->inf);
            tr = tr->right;
        }
        else {
            parents.push_back(tr->inf);
            tr = tr->left;
        }
    }
    cout << "No parents!";
}

int main() {

    // 10, 5, 15, 4, 7, 13, 17
    int x;
    Tree* tr = createTree();
    cout << "Enter the desired node: ";
    cin >> x;

    cout << "Parents: ";
    find(tr, x);

    system("pause");
    return 0;

}