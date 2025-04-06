#include <iostream>
#include <string>

using namespace std;

// двусвязный список
struct list {
    int inf;
    list *next;
    list *prev;
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

void result(list*& h, list*& t) {
    list* tmpH = h, * tmpT = t;
    while(tmpH) {
        if(tmpH->inf % 2 == 0) {
            delNode(h, t, tmpH);
            break;
        }
        tmpH = tmpH->next;
    }
    while(tmpT) {
        if(tmpT->inf % 2 == 0) {
            delNode(h, t, tmpT);
            break;
        }
        tmpT = tmpT->prev;
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