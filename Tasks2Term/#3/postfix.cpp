#include <iostream>
#include <string>

using namespace std;

struct stack {
    char inf;
    stack* next;
};

// добовляем элемент в начало стека
void push(stack*& h, char x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

// удаляем элемент и возвращаем его значение
char pop(stack*& h) {
    char x = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return x;
}

int priority(char ch) {
    if(ch == '(' || ch == ')') return 1;
    else if(ch == '+' || ch == '-') return 2;
    else if(ch == '*' || ch == '/') return 3;
    else return 0;
}

string result(string str) {
    string res = "";
    stack* h = NULL;
    int i = 0;
    while(i != str.size())  {
        int ch = str[i];
        if(priority(ch) == 0) res += ch;
        else if(ch == '(') push(h, ch);
        else if(!h && (priority(ch) == 2 || priority(ch) == 3)) push(h, ch);
        else if(ch == ')') {
            while(h->inf != '(') {
                res += pop(h);
            }
            pop(h);
        }
        else if(priority(ch) > priority(h->inf)) push(h, ch);
        else {
            while(priority(ch) <= priority(h->inf)) {
                res += pop(h);
            }
            push(h, ch);
        }
        i++;
    }
    while(h) res += pop(h);  
    return res;
}

int main() {

    string str;
    cout << "Enter expression: ";
    getline(cin, str);
    cout << "Result: " << result(str) << endl;

    // system("pause");
    return 0;

}