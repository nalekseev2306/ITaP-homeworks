#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>

// 17. Дано дерево. Определить количество узлов, имеющих только правого потомка.
using namespace std;

// структура дерева
struct Tree {
    int inf, height;
    Tree* left, * right, * parent;

    Tree(int val) : inf(val), left(nullptr),
    right(nullptr), parent(nullptr), height(1) {}
};

// >>> вывод дерева в терминал
HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

void max_height(Tree *rt, short& max, short deepness = 1) {
    if(deepness > max) max = deepness;
    if(rt->left) max_height(rt->left, max, ++deepness);
    if(rt->right) max_height(rt->right, max, ++deepness);
}

void print_helper(Tree *rt, const COORD pos, const short offset) {
    SetConsoleCursorPosition(outp, pos);
    cout << setw(offset + 1) << rt->inf;
    if (rt->left) print_helper(rt->left, {pos.X, short(pos.Y + 1)}, offset >> 1);
    if (rt->right) print_helper(rt->right, {short(pos.X + offset), short(pos.Y + 1)}, offset >> 1);
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
    if(rt) {
        short max = 1;
        max_height(rt, max);
        short width = 1 << max + 1, max_w = 128;
        if(width > max_w) width = max_w;
        while(!isSizeOfConsoleCorrect(width, max)) system("pause");
        for(short i = 0; i < max; ++i) cout << '\n';
        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD endPos = csbInfo.dwCursorPosition;
        print_helper(rt, {0, short(endPos.Y-max)}, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
    }
}
// <<< вывод дерева в терминал

int height(Tree* cur) {
    return cur ? cur->height : 0;
}

void updateHeight(Tree* cur) {
    cur->height = max(height(cur->left), height(cur->right)) + 1;
}

int balanceFactor(Tree* cur) {
    return cur ? height(cur->left) - height(cur->right): 0;
}

// >>> повороты
Tree* LLrotate(Tree* cur) {
    Tree* p = cur->left;
    cur->left = p->right;
    if (p->right) p->right->parent = cur;
    p->right = cur;
    p->parent = cur->parent;
    cur->parent = p;
    
    updateHeight(cur);
    updateHeight(p);
    return p;
}

Tree* RRrotate(Tree* cur) {
    Tree* p = cur->right;
    cur->right = p->left;
    if (p->left) p->left->parent = cur;
    p->left = cur;
    p->parent = cur->parent;
    cur->parent = p;
    
    updateHeight(cur);
    updateHeight(p);
    return p;
}
// <<< повороты

// вставка нового элемента в AVL дерево
Tree* insert(Tree* rt, int val) {
    if (!rt)
        return new Tree(val);

    if (val > rt->inf) {
        rt->right = insert(rt->right, val);
        rt->right->parent = rt;
    } 
    else if (val < rt->inf) {
        rt->left = insert(rt->left, val);
        rt->left->parent = rt;
    }

    updateHeight(rt);
    int b = balanceFactor(rt);

    // Левое поддерево перевешивает
    if (b > 1) {
        if (val < rt->left->inf)
            return LLrotate(rt);
        else {
            rt->left = RRrotate(rt->left);
            return LLrotate(rt);
        }
    }

    // Правое поддерево перевешивает
    if (b < -1) {
        if (val > rt->right->inf)
            return RRrotate(rt);
        else {
            rt->right = LLrotate(rt->right);
            return RRrotate(rt);
        }
    }

    return rt;
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
        rt = insert(rt, stoi(buf));
        str.erase(str.begin(), str.begin() + str.find_first_of(' ') + 1);
    }
    return rt;
}

// симметричный обход с условием
int count = 0;
int rightChild(Tree* rt) {
    if (rt) {
        rightChild(rt->left);
        if (!rt->left && rt->right) count++;
        rightChild(rt->right);
    }
    return count;
}

int main() {

    Tree* rt = createTree();
    print(rt);

    cout << "Number of nodes with right child: " << rightChild(rt) << endl;

    system("pause");
    return 0;

}