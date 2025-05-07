#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Tree {
    string inf;
    Tree * right, * left, * parent;

    Tree(string val) : inf(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

int priority(string ch) {
    if(ch == "(" || ch == ")") return 1;
    else if(ch == "+" || ch == "-") return 2;
    else if(ch == "*" || ch == "/") return 3;
    else return 0;
}

// разбиваем выражение на состовляющие
vector<string> getElems(string str) {
    vector<string> elems;
    while(str.find_first_of("()+-*/") != -1) {
        string buf = str.substr(0, str.find_first_of("()+-*/") + 1);
        if(buf.size() == 1) {
            elems.push_back(buf);
            str.erase(str.begin(), str.begin() + 1);
        }
        else {
            buf = str.substr(0, str.find_first_of("()+-*/"));
            elems.push_back(buf);
            str.erase(str.begin(), str.begin() + str.find_first_of("()+-*/"));
        }
    }
    elems.push_back(str);
    return elems;
}

// создаём математическое дерево
Tree* createTree(vector<string> elems) {
    Tree* rt = NULL;
    for (string elem: elems) {
        Tree* node = new Tree(elem);

        if (elem == "-" || elem == "+") {
            rt->parent = node;
            node->left = rt;
            rt = node;
        }

        else if (elem == "*" || elem == "/") {
            if(all_of(rt->inf.begin(), rt->inf.end(), ::isdigit)) {
                rt->parent = node;
                node->left = rt;
                rt = node; 
            }
            else {
                node->parent = rt;
                node->left = rt->right;
                rt->right->parent = node;
                rt->right = node;
            }
        }

        else {
            if (!rt)
                rt = node;
            else {
                if (!rt->right) {
                    node->parent = rt;
                    node->left = rt->right;
                    rt->right = node;
                }
                else {
                    Tree* cur = rt->right;
                    while (cur->right)
                        cur = cur->right;
                    node->parent = cur->parent;
                    cur->right = node;
                }
            }
        }
    }

    return rt;
}

// вывод в постфиксной форме для любых чисел
void postfix(Tree* rt) {
    if (rt) {
        postfix(rt->left);
        postfix(rt->right);
        if (all_of(rt->inf.begin(), rt->inf.end(), ::isdigit))
            cout << rt->inf + ".";
        else
            cout << rt->inf;
    }
}

// вывод в префиксной форме для любых чисел
void prefix(Tree* rt) {
    if (rt) {
        if (all_of(rt->inf.begin(), rt->inf.end(), ::isdigit))
            cout << rt->inf + ".";
        else
            cout << rt->inf;
        prefix(rt->left);
        prefix(rt->right);
    }
}

int main() {

    string str;
    cout << "Enter expression (without spaces): ";
    getline(cin, str);
    Tree* rt = createTree(getElems(str));

    cout << "Prefix notation: ";
    prefix(rt);
    cout << endl;

    cout << "Postfix notation: ";
    postfix(rt);
    cout << endl;

    system("pause");
    return 0;

}