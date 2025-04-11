#include <iostream>
#include <vector>
#include <list>

using namespace std;

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

// создание нового ребра для неориентированного графа
void addEdge(vector<list<int>>& adjList, int scr, int x) {
    adjList[scr].push_back(x);
    adjList[x].push_back(scr);
}

// алгоритм обхода в ширину
list<int> bft(vector<list<int>> adjList, int x) {
    list<int> path;
    vector<int> used(adjList.size(), 0);
    queue* h = NULL, * t = NULL;

    // отмечаем начальную вершину и добавляем в очередь
    used[x] = 1;
    path.push_back(x);
    push(h, t, x);

    while(h) {
        int tmp = pop(h, t);
        // находим все возможные непройденные вершины, в которые можно попасть из текущей
        for(auto it = adjList[tmp].begin(); it != adjList[tmp].end(); it++) { 
            if(!used[*it]) {
                used[*it] = 1;
                path.push_back(*it);
                push(h, t, *it); // добавляем их в очередь
            }
        }
    }

    return path;
}

// алгоритм обхода в глубину
list<int> dft(vector<list<int>> adjList, int x) {
    list<int> path;
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
        auto it = adjList[tmp].begin();
        // находим следующую непройденную вершину для спуска ниже
        while(it != adjList[tmp].end()) {
            if(used[*it] == 0) {
                // отмечаем и добавляем вершину в очередь и стек
                used[*it] = 1;
                path.push_back(*it);
                push(hs, *it);
                push(hq, tq, *it);
                fl = false; // продолжаем спуск
                break;
            }
            it++;
        }
        // если из вершины больше некуда попасть - удаляем её
        if(adjList[tmp].begin() == adjList[tmp].end()) pop(hs);
        // поднимаемся на предыдущую вершину
        if(fl && hs) push(hq, tq, pop(hs));
    }

    return path;
}

void printList(list<int> lst) {
    int i = 0;
    for(auto it = lst.begin(); it != lst.end(); it++, i++) {
        cout << *it;
        if(i != lst.size() - 1) cout << " -> ";
    }
}

int main() {

    // создаём неориентированный граф
    int verts = 7;
    vector<list<int>> adjList;
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
    printList(bft(adjList, 0));
    cout << endl << "Result of DFT algorithm: ";
    printList(dft(adjList, 0));

    return 0;

}