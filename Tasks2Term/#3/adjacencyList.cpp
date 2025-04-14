#include <iostream>
#include <vector>
// #include <list>

using namespace std;

// список >>>
struct Node {
    int inf;
    Node* next;
    Node* prev;

    Node(int _inf) : inf(_inf), next(nullptr), prev(nullptr) {}
};

struct list {
    Node* head;
    Node* tail;

    list() : head(nullptr), tail(nullptr) {}

    bool is_empty() {
        return head == nullptr;
    }

    void push_back(int _inf) {
        Node* p = new Node(_inf);
        if (is_empty()) {
            head = tail = p;
        } else {
            p->prev = tail;
            tail->next = p;
            tail = p;
        }
    }

    void print() {
        Node* cur = head;
        while (cur) {
            cout << cur->inf;
            if(cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << endl;
    }
};
// <<< список

// стек >>>
struct stack {
    int inf;
    stack* next;
};

void push(stack*& h, int x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop(stack*& h) {
    int x = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return x;
}
// <<< стек

// очередь >>>
struct queue {
    int inf;
    queue* next;
};

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
// <<< очередь

// создание нового ребра для неориентированного графа
void addEdge(vector<list>& adjList, int scr, int x) {
    adjList[scr].push_back(x);
    adjList[x].push_back(scr);
}

// алгоритм обхода в ширину
list bft(vector<list> adjList, int x) {
    list path;
    vector<int> used(adjList.size(), 0);
    queue* h = NULL, * t = NULL;

    // отмечаем начальную вершину и добавляем в очередь
    used[x] = 1;
    path.push_back(x);
    push(h, t, x);

    while(h) {
        int tmp = pop(h, t);
        // находим все возможные непройденные вершины, в которые можно попасть из текущей
        Node* r = adjList[tmp].head;
        while(r) {
            if(!used[r->inf]) {
                used[r->inf] = 1;
                path.push_back(r->inf);
                push(h, t, r->inf); // добавляем их в очередь
            }
            r = r->next;
        }
    }

    return path;
}

// алгоритм обхода в глубину
list dft(vector<list> adjList, int x) {
    list path;
    stack* hs = NULL; // стек дял возвращения на предыдущие вершины
    queue* hq = NULL, * tq = NULL;
    vector<int> used(adjList.size(), 0);

    // отмечаем начальную вершину и добавляем в очередь и в стек
    used[x] = 1;
    path.push_back(x);
    push(hs, x);
    push(hq, tq, x);

    while(hq) {
        bool fl = true; // отвечает за подъём на предыдущую вершину
        int tmp = pop(hq, tq);
        Node* r = adjList[tmp].head;
        // находим следующую непройденную вершину для спуска ниже
        while(r) {
            if(!used[r->inf]) {
                // отмечаем и добавляем вершину в очередь и стек
                used[r->inf] = 1;
                path.push_back(r->inf);
                push(hs, r->inf);
                push(hq, tq, r->inf);
                fl = false; // продолжаем спуск
                break;
            }
            r = r->next;
        }
        // поднимаемся на предыдущую вершину
        if(fl && hs) push(hq, tq, pop(hs));
    }

    return path;
}

int main() {

    // создаём неориентированный граф
    int verts = 7;
    vector<list> adjList;
    adjList.resize(verts);
    addEdge(adjList, 0, 1);
    addEdge(adjList, 0, 2);
    addEdge(adjList, 0, 4);
    addEdge(adjList, 0, 5);
    addEdge(adjList, 1, 3);
    addEdge(adjList, 2, 5);
    addEdge(adjList, 5, 6);
    addEdge(adjList, 6, 4);

    // результат работы двух алгоритмов
    cout << "Result of BFT algorithm: ";
    bft(adjList, 0).print();
    cout << "Result of DFT algorithm: ";
    dft(adjList, 0).print();

    return 0;

}