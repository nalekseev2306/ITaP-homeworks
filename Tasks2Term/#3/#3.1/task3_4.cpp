#include <iostream>
#include <string>

using namespace std;

struct queue {
    int inf;
    queue* next;
};

// вставляем элемент в конец очереди
void push(queue*& h, queue*& t, int x) {
    queue* r = new queue;
    r->inf = x;
    r->next = NULL;
    if(!h && !t) {
        h = t = r;
    }
    else {
        t->next = r;
        t = r;
    }
}

// удаляем перывй элемент в очереди и возвращаем его значение
int pop(queue*& h, queue*& t) {
    int x = h->inf;
    queue* r = h;
    h = h->next;
    if(!h) {
        t = NULL;
    }
    delete r;
    return x;
}

// переводим строку в очередь
pair<queue*, queue*> strToQueue() {
    queue* h = NULL, * t = NULL;
    string str;
    cout << "Enter sequence: ";
    getline(cin, str);
    str += ' ';
    while(str != "") {
        int buf = stoi(str.substr(0, str.find_first_of(' ')));
        push(h, t, buf);
        str.erase(str.begin(), str.begin() + str.find_first_of(' ') + 1);
    }
    return pair(h, t);
}

// находим максимальный элемент
int maxElem(queue* h, queue* t) {
    long long int max = -1e10;
    while(h) {
        int x = h->inf;
        if(x > max) max = x;
        h = h->next;
    }
    return max;
}

void result(queue*& h, queue*& t) {
    queue* hTmp = NULL, * tTmp = NULL;
    int max = maxElem(h, t), last = t->inf;
    while(h && t) {
        if(h->inf == last) {
            push(hTmp, tTmp, pop(h, t));
            push(hTmp, tTmp, max);
        }
        else push(hTmp, tTmp, pop(h, t));
    }
    h = hTmp;
    t = tTmp;
}

int main() {

    pair<queue*, queue*> que = strToQueue();
    result(que.first, que.second);

    cout << "Result: ";
    while(que.first && que.second) {
        cout << pop(que.first, que.second) << ' ';
    }
    cout << endl;

    system("pause");
    return 0;

}