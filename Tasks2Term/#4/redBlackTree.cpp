#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>

// 1. Дано дерево. Подсчитать сумму листьев.
using namespace std;

#define RED true
#define BLACK false

// структура дерева
struct Tree {
    int inf;
    bool color;
    Tree* left, * right, * parent;
    Tree(int val) : inf(val), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

// >>> вывод дерева в терминал
HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

void max_height(Tree *rt, short& max, short deepness = 1) {
    if(deepness > max) max = deepness;
    if(rt->left) max_height(rt->left, max, ++deepness);
    if(rt->right) max_height(rt->right, max, ++deepness);
}

void print_helper(Tree *x, const COORD pos, const short offset) {
    SetConsoleTextAttribute(outp, x->color == RED ? 12 : 8);
    SetConsoleCursorPosition(outp, pos);
    cout << setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, {pos.X, short(pos.Y + 1)}, offset >> 1);
    if (x->right) print_helper(x->right, {short(pos.X + offset), short(pos.Y + 1)}, offset >> 1);
}

bool isSizeOfConsoleCorrect(const short& width,const short& height){
    GetConsoleScreenBufferInfo(outp, &csbInfo);
    COORD szOfConsole = csbInfo.dwSize;
    if(szOfConsole.X < width && szOfConsole.Y < height) cout << "Please increase the height and width of the terminal. ";
    else if(szOfConsole.X < width) cout << "Please increase the width of the terminal. ";
    else if(szOfConsole.Y < height) cout << "Please increase the height of the terminal. ";
    if(szOfConsole.X < width || szOfConsole.Y < height) {
        cout << "Size of your terminal now: " << szOfConsole.X << ' '
        << szOfConsole.Y << ". Minimum required: " << width << ' ' << height << ".\n";
        return false;
    }
   return true;
}

void print(Tree* rt) {
    if (rt) {
        short max = 1;
        max_height(rt, max);
        short width = 1 << max + 1, max_w = 128; // вычисляем ширину вывода
        if (width > max_w) width = max_w;
        while (!isSizeOfConsoleCorrect(width, max)) system("pause");
        for (short i = 0; i < max; ++i) cout << '\n'; // резервируем место для вывода
        GetConsoleScreenBufferInfo(outp, &csbInfo); // получаем данные
        COORD endPos = csbInfo.dwCursorPosition;
        print_helper(rt, {0, short(endPos.Y - max)}, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
        SetConsoleTextAttribute(outp, 7);
    }
}
// <<< вывод дерева в терминал

// >>> нахождение родственников для упрощения алгоритмов
Tree* grandparent(Tree* cur) {
    return cur && cur->parent ? cur->parent->parent: nullptr; 
}

Tree* uncle(Tree* cur) {
    Tree* g = grandparent(cur);
    if(!g) return nullptr;
    return cur->parent == g->left ? g->right: g->left;
}

Tree* sibling(Tree* cur) {
    if(cur && cur->parent) {
        return cur == cur->parent->left ? cur->parent->right: cur->parent->left;
    }
    else return nullptr;
}
// <<< нахождение родственников для упрощения алгоритмов

// >>> повороты
bool isLeaf(Tree* cur) {
    return cur->left || cur->right;
}

void leftRotate(Tree* cur, Tree*& rt) {
    Tree* y = cur->right;
    cur->right = y->left;
    if(y->left)
        if(!isLeaf(y->left)) y->left->parent = cur;

    y->parent = cur->parent;
    if(!cur->parent) rt = y;
    else cur == cur->parent->left ? cur->parent->left = y: cur->parent->right = y;

    y->left = cur;
    cur->parent = y;
    if(!y->parent) y->color = BLACK;
}

void rightRotate(Tree* cur, Tree*& rt) {
    Tree* y = cur->left;
    cur->left = y->right;
    if(y->right)
        if(!isLeaf(y->right)) y->right->parent = cur;

    y->parent = cur->parent;
    if(!cur->parent) rt = y;
    else cur == cur->parent->left ? cur->parent->left = y: cur->parent->right = y;

    y->right = cur;
    cur->parent = y;
    if(!y->parent) y->color = BLACK;
}
// <<< повороты

// >>> вставка нового элемента в дерево
void insertCase5(Tree*& rt, Tree* cur) {
    Tree* g = grandparent(cur);
    cur->parent->color = BLACK;
    if(g) {
        g->color = RED;
        cur == cur->parent->left && cur->parent == g->left ?
        rightRotate(g, rt): leftRotate(g, rt);
    }
}

void insertCase4(Tree*& rt, Tree* cur) {
    Tree* g = grandparent(cur);
    if(g && cur == cur->parent->right && cur->parent == g->left) {
        leftRotate(cur->parent, rt);
        cur = cur->left;
    }
    else if(g && cur == cur->parent->left && cur->parent == g->right) {
        rightRotate(cur->parent, rt);
        cur = cur->right;
    }
    insertCase5(rt, cur);
}

void insertCase1(Tree*& rt, Tree* cur);
void insertCase3(Tree*& rt, Tree* cur) {
    Tree* u = uncle(cur);
    Tree* g = grandparent(cur);
    if(u && u->color == RED && cur->parent->color == RED) {
        cur->parent->color = BLACK;
        u->color = BLACK;
        if(g) {
            g->color = RED;
            insertCase1(rt, g);
        }
    }
    else insertCase4(rt, cur);
}

void insertCase2(Tree*& rt, Tree* cur) {
    if(cur->color == RED) insertCase3(rt, cur);
}

void insertCase1(Tree*& rt, Tree* cur) {
    if(!cur->parent) cur->color = BLACK;
    else insertCase2(rt, cur);
}

void insert(Tree*& rt, Tree* prev, int val) {
    Tree* p = new Tree(val);
    if(!rt) {
        p->color = BLACK;
        rt = p;
    }
    else if(val < prev->inf && !prev->left) {
        p->parent = prev;
        prev->left = p;
        insertCase1(rt, prev->left);
    }
    else if(val > prev->inf && !prev->right) {
        p->parent = prev;
        prev->right = p;
        insertCase1(rt, prev->right); 
    }
    else if(val < prev->inf && prev->left) insert(rt, prev->left, val);
    else if(val > prev->inf && prev->right) insert(rt, prev->right, val);
}
// <<< вставка нового элемента в дерево

// >>> удаляем звено дерева
void deleteCase2(Tree*& rt, Tree* cur);
void deleteCase3(Tree*& rt, Tree* cur);
void deleteCase4(Tree*& rt, Tree* cur);
void deleteCase5(Tree*& rt, Tree* cur);
void deleteCase6(Tree*& rt, Tree* cur);

void deleteCase1(Tree*& rt, Tree* cur) {
    if(!cur->parent)
        cur->left ? rt = cur->left: rt = cur->right;
    else deleteCase2(rt, cur); 
}

void deleteCase2(Tree*& rt, Tree* cur) {
    Tree* s = sibling(cur);
    if(s->color == RED) {
        cur->parent->color = RED;
        s->color = BLACK;
        cur == cur->parent->left ?
        leftRotate(cur->parent, rt): rightRotate(cur->parent, rt);
    }
    deleteCase3(rt, cur);
}

void deleteCase3(Tree*& rt, Tree* cur) {
    Tree* s = sibling(cur);
    if(cur->parent->color == BLACK && s->color == BLACK
        && (isLeaf(s->left) || s->left->color == BLACK)
        && (isLeaf(s->right) || s->right->color == BLACK)) {
            s->color = RED;
            deleteCase1(rt, cur);
        }
    else deleteCase4(rt, cur);
}

void deleteCase4(Tree*& rt, Tree* cur) {
    Tree* s = sibling(cur);
    if(cur->parent->color == RED && s->color == BLACK
        && (isLeaf(s->left) || s->left->color == BLACK)
        && (isLeaf(s->right) || s->right->color == BLACK)) {
            s->color = RED;
            cur->parent->color = BLACK;
        }
    else deleteCase5(rt, cur);
}

void deleteCase5(Tree*& rt, Tree* cur) {
    Tree* s = sibling(cur);
    if(s->color == BLACK) {
        if(cur == cur->parent->left
            && (!isLeaf(s->left) && s->left->color == RED)
            && (isLeaf(s->right) || s->right->color == BLACK)) {
                s->color = RED;
                s->left->color = BLACK;
                rightRotate(s, rt);
        }
        else if(cur == cur->parent->right
            && (!isLeaf(s->right) && s->right->color == RED)
            && (isLeaf(s->left) || s->left->color == BLACK)) {
                s->color = RED;
                s->right->color = BLACK;
                leftRotate(s, rt);
        }
    }
    deleteCase6(rt, cur);
}

void deleteCase6(Tree*& rt, Tree* cur) {
    Tree* s = sibling(cur);
    s->color = cur->parent->color;
    cur->parent->color = BLACK;
    if(cur == cur->parent->left) {
        s->right->color = BLACK;
        leftRotate(cur->parent, rt);
    }
    else {
        s->left->color = BLACK;
        rightRotate(cur->parent, rt);
    }
}

void replace(Tree*& rt, Tree* cur) {
    if(cur->left) {
        Tree* ch = cur->left;
        ch->parent = cur->parent;
        if(cur->parent) {
            cur == cur->parent->left ? 
            cur->parent->left = ch:
            cur->parent->right = ch;
        }
    }
    else {
        Tree* ch = cur->right;
        ch->parent = cur->parent;
        if(cur->parent) {
            cur == cur->parent->left ? 
            cur->parent->left = ch:
            cur->parent->right = ch;
        }
    }
}

void deleteNode(Tree*& rt, Tree* cur) {
    if(cur->left && cur->right) {
        Tree* buf;
        if(cur->inf <= rt->inf) {
            buf = cur->left;
            while (buf && buf->right)
                buf = buf->right;
        }
        else {
            buf = cur->right;
            while (buf && buf->left)
                buf = buf->left;
        }
        int tmp = buf->inf;
        buf->inf = cur->inf;
        cur->inf = tmp;
        cur = buf;
    }
    if(cur->left || cur->right) {
        Tree* ch;
        if(cur->left && !cur->right) ch = cur->left;
        if(!cur->left && cur->right) ch = cur->right;
        replace(rt, cur);
        if(cur->color == BLACK)
            if(ch->color == RED) ch->color = BLACK;
            else deleteCase1(rt, cur);
    }
    else {
        if(cur->color == BLACK) deleteCase1(rt, cur);
        else {
            cur == cur->parent->left ?
            cur->parent->left = nullptr:
            cur->parent->right = nullptr;
        }
    }
    delete cur;
}
// <<< удаляем звено дерева

// симметричный обход с условием
void findLeaves(Tree* rt, vector<Tree*>& vec) {
    if(rt) {
        findLeaves(rt->left, vec);
        if(!rt->left && !rt->right) vec.push_back(rt);
        findLeaves(rt->right, vec);
    }
}

// считать строку и создать дерево
Tree* createTree() {
    string str;
    Tree* rt = NULL;
    cout << "Enter sequence: ";
    getline(cin, str);
    str += ' ';
    while(str != "") {
        string buf = str.substr(0, str.find_first_of(' '));
        insert(rt, rt, stoi(buf));
        str.erase(str.begin(), str.begin() + str.find_first_of(' ') + 1);
    }
    return rt;
}

int main() {

    // 15 11 22 6 13 17 25 1 8 27
    vector<Tree*> l;
    Tree* rt = createTree();

    findLeaves(rt, l);
    int sum = 0;
    for(auto i: l) sum += i->inf;
    cout << "Sum of leaves = " << sum << endl;

    cout << "Red-black tree: " << endl;
    print(rt);

    int x;
    cout << "Enter node: ";
    cin >> x;
    Tree* del = rt;
    while(x != del->inf && del) {
        if(x < del->inf) del = del->left;
        else del = del->right;
    }
    deleteNode(rt, del);

    cout << "Red-black tree: " << endl;
    print(rt);

    system("pause");
    return 0;

}