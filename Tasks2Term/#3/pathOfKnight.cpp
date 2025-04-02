#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct queue {
    pair<int, int> inf;
    queue* next;
};

void push(queue*& h, queue*& t, pair<int, int> x) {
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

pair<int, int> pop(queue*& h, queue*& t) {
    pair<int, int> x = h->inf;
    queue* r = h;
    h = h->next;
    if(!h) {
        t = NULL;
    }
    delete r;
    return x;
}

struct list {
    pair<int, int> inf;
    list *next;
    list *prev;
};

void push(list*& h, list*& t, pair<int, int> x) {
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

void reverse(list*& h, list*& t) {
    list* tmpH = NULL, * tmpT = NULL;
    while(t) {
        push(tmpH, tmpT, t->inf);
        t = t->prev;
    }
    h = tmpH;
    t = tmpT;
}

// вектор всех возможных ходов коня
const vector<pair<int, int>> moves = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                                    {1, -2}, {1, 2}, {2, -1}, {2, 1}};

// поиск кратчайшего пути шахматного коня
pair<list*, list*> findPath(pair<int, int> start, pair<int, int> end) {
    map<pair<int, int>, pair<int, int>> visited;
    queue* queH = NULL, * queT = NULL;
    bool found = false;
    push(queH, queT, start);
    visited[start] = {-1, -1};

    // алгоритм обхода в ширину
    while(queH) {

        pair<int, int> cur = pop(queH, queT);
        if(cur == end) {
            found = true;
            break;
        }

        for(auto move: moves) {
            pair<int, int> next = {cur.first + move.first, cur.second + move.second};
            if(1 <= next.first && next.first <= 8 && 1 <= next.second && next.second <= 8
                && visited.find(next) == visited.end()) {
                push(queH, queT, next);
                visited[next] = cur;
            }
        }

    }

    list* pathH = NULL, * pathT = NULL;
    if(!found) return {pathH, pathT};

    // восстанавливаем путь
    pair<int, int> cur = end;
    while(cur != make_pair(-1, -1)) {
        push(pathH, pathT, cur);
        cur = visited[cur];
    }
    reverse(pathH, pathT);
    return {pathH, pathT};

}

// переводим позицию в шахматную нотацию
string toNotation(pair<int, int> pos) {
    string alph = "ABCDEFGH";
    string digits = "12345678";
    string res;
    res += alph[pos.first - 1];
    res += digits[pos.second - 1];
    return res;
}

// переводим шахматную нотацию в позицию
pair<pair<int, int>, pair<int, int>> notation() {
    string str, alph = "ABCDEFGH";
    pair<int, int> pos1, pos2;
    cout << "Enter notation (A1 H8): ";
    while(true) {
        getline(cin, str); 
        if(str.size() == 5) {
            pos1.first = alph.find_first_of(toupper(str[0])) + 1;
            pos1.second = stoi(&str[1]);
            pos2.first = alph.find_first_of(toupper(str[3])) + 1;
            pos2.second = stoi(&str[4]);
            break;
        }
        else cout << "Try again!" << endl;
    }
    return {pos1, pos2};
}

int main() {

    pair<pair<int, int>, pair<int, int>> pos = notation();
    pair<int, int> start = pos.first, end = pos.second;
    pair<list*, list*> ans = findPath(start, end);

    cout << "Shortest path: ";
    while(ans.first) {
        string nota = toNotation(ans.first->inf);
        cout << nota << ' ';
        ans.first = ans.first->next;
    }

    system("pause");
    return 0;

}