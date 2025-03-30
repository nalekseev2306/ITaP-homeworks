#include <iostream>
#include <string>

using namespace std;

struct list {
    int inf;
    list* next;
    list* prev;
};

// добавляем элемент в конец списка
void push(list*& h, list*& t, int x) {
    list *r = new list;
    r->inf = x;
    r->next = NULL;
    if(!h && !t) {
        r->prev = NULL;
        h = r;
    }
    else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

// удаление элемента
void delNode(list*& h, list*& t, list* r) {
    if(r == h && r == t) h = t = NULL;
    else if(h == r) {
        h = h->next;
        h->prev = NULL;
    }
    else if(t == r) {
        t = t->prev;
        t->next = NULL;
    }
    else {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
}

// переводим в список
pair<list*, list*> strToList() {
    list* h = NULL, * t = NULL;
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

// вывести список
void print(list* h, list* t) {
    while(h) {
        cout << h->inf << ' ';
        h = h->next;
    }
    cout << endl;
}

// вставить элемент после указанного элемента
void insertAfter(list*& h, list*& t, list* r, int x) {
    list* p = new list;
    p->inf = x;
    if(r == t) {
        p->next = NULL;
        p->prev = r;
        r->next = p;
        t = p;
    }
    else {
        r->next->prev = p;
        p->next = r->next;
        p->prev = r;
        r->next = p;
    }
}

void result(list*& h, list*& t) {
    list* r = h;
    list* lastOdd = NULL;
    int firstElem = h->inf;
    bool fl = true;
    while(r) {
        if(r->inf % 2 != 0) {
            list* tmp = r;
            if(fl && firstElem % 2 == 0) {
                list* p = new list;
                p->inf = r->inf;
                p->prev = NULL;
                p->next = h;
                h = p;
                lastOdd = h;
                r = r->next;
                delNode(h, t, tmp);
                fl = false;
            }
            else if(fl && firstElem % 2 != 0) {
                lastOdd = r;
                r = r->next;
                fl = false;
            }
            else {
                insertAfter(h, t, lastOdd, r->inf);
                lastOdd = lastOdd->next;
                r = r->next;
                delNode(h, t, tmp);
            }
        }
        else r = r->next;
    }
}

int main() {

    pair<list*, list*> lst = strToList();
    result(lst.first, lst.second);
    cout << "Result: ";
    print(lst.first, lst.second);

    system("pause");
    return 0;

}