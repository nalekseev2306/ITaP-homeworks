#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct stack {
    string inf;
    stack* next;
};

// добовляем элемент в начало стека
void push(stack*& h, string x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

// удаляем элемент и возвращаем его значение
string pop(stack*& h) {
    string x = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return x;
}

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

// переводим из инфиксной записи в постфиксную
string result(string str) {
    string res = "";
    vector<string> elems = getElems(str);
    stack* h = NULL;
    int i = 0;
    while(i != elems.size())  {
        string ch = elems[i];
        if(ch.size() > 1) ch += ".";
        if(priority(ch) == 0) res += ch;
        else if(ch == "(") push(h, ch);
        else if(!h && (priority(ch) == 2 || priority(ch) == 3)) push(h, ch);
        else if(ch == ")") {
            while(h->inf != "(") {
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

    system("pause");
    return 0;

}