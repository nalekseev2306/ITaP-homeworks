#include <iostream>
#include <vector>
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

vector<int> pr;
vector<int> used;
vector<vector<int>> cycles;

// добавляем цикл
void addCycles(int start, int end) {
    vector<int> tmp;
    int cur = end;
    
    while (cur != start) {
        tmp.push_back(cur);
        cur = pr[cur];
    }
    tmp.push_back(start);
    reverse(tmp.begin(), tmp.end());
    tmp.push_back(start);
    cycles.push_back(tmp);
}

// обход в глубину с условием
void dfsCycle(vector<vector<int>> graph, int x) {
    used[x] = 1; // помечаем как посещённую

    for (int i = 0; i < graph[x].size(); ++i) {
        if (pr[x] == graph[x][i]) continue;
        if (!used[graph[x][i]]) {
            pr[graph[x][i]] = x;
            dfsCycle(graph, graph[x][i]);
        } 
        else if (used[graph[x][i]] == 1) {
            addCycles(graph[x][i], x);
        }
    }

    used[x] = 2; // помечаем как обработанную
}

// удаляем дубликаты циклов
void rmDuplicates() {
    for (int i = 0; i < cycles.size(); i++)
        cycles[i].erase(unique(cycles[i].begin(), cycles[i].end()), cycles[i].end());
}

int main() {

    char orient;
    pair<int, vector<Edge>> edges = readEdes("data.txt");

    cout << "Will graph be oriented? (y/n): ";
    cin >> orient;
    vector<vector<int>> graph = createGraph(edges.second, edges.first, orient);

    pr.resize(edges.first, -1);
    used.resize(edges.first, 0);

    for (int i = 0; i < edges.first; ++i) {
        if (!used[i])
            dfsCycle(graph, i);
    }
    rmDuplicates();

    if (cycles.empty()) {
        cout << "There are no cycles!" << endl;
    } else {
        cout << "Cycles found: " << cycles.size() << endl;
        for (int i = 0; i < cycles.size(); i++) {
            cout << "Cycle " << i+1 << ": ";
            for (int vert : cycles[i]) {
                cout << vert << " ";
            }
            cout << endl;
        }
    }

    system("pause");
    return 0;

}