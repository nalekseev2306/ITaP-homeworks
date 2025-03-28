#include <iostream>
#include <string>

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

// переворачиваем стек
stack* reverse(stack* h) {
    stack* tmp = NULL;
    while(h) {
        push(tmp, pop(h));
    }
    h = tmp;
    return h;
}

// переводим строку букв в стек
stack* strToStack() {
    stack* h = NULL;
    string str;
    cout << "Enter letters: ";
    getline(cin, str);
    str += ' ';
    while(str != "") {
        string buf = str.substr(0, str.find_first_of(' '));
        push(h, buf);
        str.erase(str.begin(), str.begin() + str.find_first_of(' ') + 1);
    }
    return reverse(h);
}

// считаем количество согласных букв
int cntsogl(stack* h) {
    int count = 0;
    while(h) {
        string buf = h->inf;
        if(buf.find_first_of("qwrtpsdfghjklzxcvbnm") != -1) count++;
        h = h->next;
    }
    return count;
}

stack* result(stack* h) {
    stack* tmp = NULL;
    int count = cntsogl(h);
    while(h) {
        string buf = pop(h);
        if(count == 1 && buf.find_first_of("qwrtpsdfghjklzxcvbnm") != -1) {
            push(tmp, buf);
            push(tmp, "?");
        }
        else if(buf.find_first_of("qwrtpsdfghjklzxcvbnm") != -1) {
            push(tmp, buf);
            count--;
        }
        else push(tmp, buf);
    }
    return reverse(tmp);
}

int main() {

    stack* h = strToStack();
    stack* res = result(h);
    
    cout << "Result: ";
    while(res) {
        cout << pop(res) << ' ';
    }
    cout << endl;

    system("pause");
    return 0;

}