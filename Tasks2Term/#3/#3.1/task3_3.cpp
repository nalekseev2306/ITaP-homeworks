#include <iostream>
#include <string>

using namespace std;

struct stack {
    int inf;
    stack* next;
};

// добовляем элемент в начало стека
void push(stack*& h, int x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

// удаляем элемент и возвращаем его значение
int pop(stack*& h) {
    int x = h->inf;
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

// переводим строку в стек
stack* strToStack() {
    stack* h = NULL;
    string str;
    cout << "Enter sequence: ";
    getline(cin, str);
    str += ' ';
    while(str != "") {
        int buf = stoi(str.substr(0, str.find_first_of(' ')));
        push(h, buf);
        str.erase(str.begin(), str.begin() + str.find_first_of(' ') + 1);
    }
    return reverse(h);
}

// ищем максимальный элементв в стеке
int maxElem(stack* h) {
    long long int max = -1e10;
    while(h) {
        int x = h->inf;
        if(x > max) max = x;
        h = h->next;
    }
    return max;
}

// ищем минимальный элемент в стеке
int minElem(stack* h) {
    long long int min = 1e10;
    while(h) {
        int x = h->inf;
        if(x < min) min = x;
        h = h->next;
    }
    return min;
}

// считаем количество минимальных элементов
int cntMin(stack* h) {
    int count = 0;
    int min = minElem(h);
    while(h) {
        int x = h->inf;
        if(x == min) count++;
        h = h->next;
    }
    return count;
}

stack* result(stack* h) {
    stack* tmp = NULL;
    int cnt = cntMin(h), min = minElem(h), max = maxElem(h);
    bool fl = true;
    while(h) {
        int x = pop(h);
        if(fl && x == min) {
            push(tmp, x);
            push(tmp, max);
            fl = false;
            cnt--;
        }
        else if(cnt == 1 && x == min) {
            push(tmp, x);
            push(tmp, max);
        }
        else if(x == min) {
            push(tmp, x);
            cnt--;
        }
        else push(tmp, x);
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