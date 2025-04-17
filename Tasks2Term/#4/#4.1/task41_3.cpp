#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>

using namespace std;

// структура дерева
struct Tree {
    int inf;
    Tree* left, * right;
    Tree* parent;

    Tree(int val) : inf(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

// >>> вывод дерева в терминал
HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

void max_height(Tree *rt, short& max, short deepness = 1) { //требует проверки на существование корня
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
        << szOfConsole.Y << ".Minimum required: " << width << ' ' << height << ".\n";
        return false;
    }
   return true;
}

void print(Tree* rt) {
    if(rt) {
        short max = 1;
        max_height(rt, max);
        short width = 1 << max + 1, max_w = 128; // вычисляем ширину вывода
        if(width > max_w) width = max_w;
        while(!isSizeOfConsoleCorrect(width, max)) system("pause");
        for(short i = 0; i < max; ++i) cout << '\n'; // резервируем место для вывода
        GetConsoleScreenBufferInfo(outp, &csbInfo); // получаем данные
        COORD endPos = csbInfo.dwCursorPosition;
        print_helper(rt, {0, short(endPos.Y-max)}, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
    }
}
// <<< вывод дерева в терминал

// вставка нового элемента в дерево
void insert(Tree*& rt, int val) {
    Tree* p = new Tree(val);
    if(!rt) rt = p;
    else if(val > rt->inf) {
        if (rt->right) {
            insert(rt->right, val);
        }
        else {
            rt->right = p;
            rt->right->parent = rt;
        }
    }
    else if(val < rt->inf){
        if (rt->left) {
            insert(rt->left, val);
        }
        else {
            rt->left = p;
            rt->left->parent = rt;
        }
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
        insert(rt, stoi(buf));
        str.erase(str.begin(), str.begin() + str.find_first_of(' ') + 1);
    }
    return rt;
}

// находим листья симметричным обходом
void findLeaves(Tree* rt, vector<Tree*>& vec) {
    if(rt) {
        findLeaves(rt->left, vec);
        if(!rt->left && !rt->right) vec.push_back(rt);
        findLeaves(rt->right, vec);
    }
}

// находим средний по значению лист
Tree* meanLeaves(Tree* rt) {
    vector<Tree*> vec;
    findLeaves(rt, vec);
    if(vec.size() % 2 != 0) return vec[(vec.size() - 1) / 2];
    else {
        int sum = 0, count = vec.size();
        for(Tree* leaf: vec) sum += leaf->inf;
        float mean = sum / count;
        return
        abs(mean - vec[vec.size() / 2]->inf) < abs(mean - vec[(vec.size() / 2) - 1]->inf) ?
        vec[vec.size() / 2]: vec[(vec.size() / 2) - 1];
    }
}

// наименьший узел в правом поддереве
Tree* getSuccessor(Tree* cur){
    cur = cur->right;
    while (cur && cur->left)
        cur = cur->left;
    return cur;
}

// удаляем звено дерева
Tree* delNode(Tree* rt, int x){

    if(!rt) return rt;

    if (rt->inf > x)
        rt->left = delNode(rt->left, x);
    else if (rt->inf < x)
        rt->right = delNode(rt->right, x);

    else {
        // только правый ребёнок или отсутствуют оба
        if(!rt->left) {
            Tree* tmp = rt->right;
            delete rt;
            return tmp;
        }
        // только левый ребёнок
        if(!rt->right) {
            Tree* tmp = rt->left;
            delete rt;
            return tmp;
        }
        // оба ребёнка
        Tree* succ = getSuccessor(rt);
        rt->inf = succ->inf;
        rt->right = delNode(rt->right, succ->inf);
    }
    return rt;
}

int main() {

    // 10 5 15 4 7 13 17
    Tree* rt = createTree();
    cout << "Start tree: " << endl;
    print(rt);

    Tree* grandfather = meanLeaves(rt)->parent->parent;
    if(grandfather) {
        rt = delNode(rt, grandfather->inf);
        cout << "Finish tree: " << endl;
        print(rt);
    }
    else cout << "Grandfather dont exist!" << endl;

    system("pause");
    return 0;

}