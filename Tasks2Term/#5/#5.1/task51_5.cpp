#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <map>

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

vector<int> findPath(vector<vector<int>> graph, int start, int end) {
    map<int, int> visited;
    queue<int> que;
    bool found = false;
    que.push(start);
    visited[start] = -1;

    // алгоритм обхода в ширину
    while (!empty(que)) {
        int cur = que.front();
        que.pop();

        if (cur == end) {
            found = true;
            break;
        }

        for (int next: graph[cur]) {
            if (visited.find(next) == visited.end()) {
                que.push(next);
                visited[next] = cur;
            }
        }
    }

    // восстанавливаем путь
    vector<int> path;
    if (!found) return {-1};

    int cur = end;
    while (cur != -1) {
        path.insert(path.begin(), cur);
        cur = visited[cur];
    }

    return path;
}

int main() {

    char orient;
    pair<int, vector<Edge>> edges = readEdes("data.txt");

    cout << "Will graph be oriented? (y/n): ";
    cin >> orient;
    vector<vector<int>> graph = createGraph(edges.second, edges.first, orient);
    cin.clear();
    cin.sync();

    int a, b;
    string str;
    cout << "Enter two vertices (a b): ";
    getline(cin, str);
    istringstream iss(str);
    iss >> a >> b;

    if (a < edges.first && b < edges.first) {
        for (int vert: findPath(graph, a, b))
            cout << vert << ' ';
        cout << endl;
    }
    else cout << "Vertices dosnt exist!";

    system("pause");
    return 0;

}