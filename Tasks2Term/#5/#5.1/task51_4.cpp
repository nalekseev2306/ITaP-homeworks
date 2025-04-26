#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// структура ребра
struct Edge {
    int x, y;
    Edge(int _x, int _y) : x(_x), y(_y) {}
};

// считываем данные из файла
pair<int, vector<Edge>> readEdes(const string& fileName) {
    int n;
    vector<Edge> edges;
    ifstream file(fileName);

    string line;
    getline(file, line);
    istringstream iss(line);
    iss >> n;

    while (getline(file, line)) {
        istringstream iss(line);
        int x, y;
        iss >> x >> y;
        edges.push_back(Edge(x, y));
    }

    return pair{n, edges};
}

// создаём список смежности
vector<vector<int>> createGraph(vector<Edge> edges, int n, char oriented) {
    vector<vector<int>> graph;
    graph.resize(n);
    for (Edge edge: edges) {
        if (oriented == 'y') {
            if (edge.x < n && edge.y < n) {
                graph[edge.x].push_back(edge.y);
            }
        }
        else {
            if (edge.x < n && edge.y < n) {
                graph[edge.x].push_back(edge.y);
                graph[edge.y].push_back(edge.x);
            }
        }
    }
    for (auto &vert: graph) {
        sort(vert.begin(), vert.end());
        vert.erase(unique(vert.begin(), vert.end()), vert.end());
    }
    return graph;
}

vector<int> parent;
vector<int> used;
vector<vector<int>> cycles;
vector<vector<int>> cyclesSort;

// добавляем цикл
void addCycles(int start, int end) {
    vector<int> tmp;
    int cur = end;
    
    while (cur != start) {
        tmp.push_back(cur);
        cur = parent[cur];
    }
    tmp.push_back(start);

    if (tmp.size() > 2) {
        reverse(tmp.begin(), tmp.end());
        cycles.push_back(tmp);
        sort(tmp.begin(), tmp.end());
        cyclesSort.push_back(tmp);
    }
}

// обход в глубину с условием
void dfsCycle(vector<vector<int>> graph, int start) {
    used[start] = 1; // помечаем как посещённую

    for (auto cur: graph[start]) {
        if (parent[cur] == start) continue;
        if (!used[cur]) {
            parent[cur] = start;
            dfsCycle(graph, cur);
        } 
        else if (used[cur] == 1) {
            addCycles(cur, start);
        }
    }

    used[start] = 0; // помечаем как обработанную
}

// удаляем дубликаты циклов
void rmDduplicates() {
    for (int i = 0; i < cyclesSort.size(); i++) {
        for (int j = i + 1; j < cyclesSort.size(); ) {
            if (cyclesSort[i] == cyclesSort[j]) {
                cyclesSort.erase(cyclesSort.begin() + j);
                cycles.erase(cycles.begin() + j);
            }
            else {
                j++;
            }
        }
    }
}

int main() {

    char orient;
    pair<int, vector<Edge>> edges = readEdes("data.txt");

    cout << "Will graph be oriented? (y/n): ";
    cin >> orient;
    vector<vector<int>> graph = createGraph(edges.second, edges.first, orient);

    parent.resize(edges.first, -1);
    used.resize(edges.first, 0);

    // для каждой вершины ищем циклы
    for (int i = 0; i < edges.first; i++) {
        if (!used[i])
            dfsCycle(graph, i);
    }
    rmDduplicates();

    // выводим циклы
    if (cycles.empty()) {
        cout << "There are no cycles!" << endl;
    }
    else {
        cout << "Cycles found: " << cycles.size() << endl;
        for (auto cycle: cycles) {
            static int i = 0;
            cout << "Cycle " << ++i << ": ";
            for (int vert : cycle) {
                cout << vert << " ";
            }
            cout << cycle[0] << endl;
        }
    }
    
    system("pause");
    return 0;

}