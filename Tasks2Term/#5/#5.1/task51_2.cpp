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

int main() {

    char orient;
    pair<int, vector<Edge>> edges = readEdes("data.txt");

    cout << "Will graph be oriented? (y/n): ";
    cin >> orient;
    vector<vector<int>> graph = createGraph(edges.second, edges.first, orient);
    cin.clear();
    cin.sync();

    int x, y;
    string str;
    cout << "Enter new edge (x y): ";
    getline(cin, str);
    istringstream iss(str);
    iss >> x >> y;

    // вставляем новое ребро
    if (x < edges.first && y < edges.first) {
        graph[x].push_back(y);
        sort(graph[x].begin(), graph[x].end());
        for (int vert: graph[x]) 
            cout << vert << ' ';
        cout << endl;
    }
    else
        cout << "Edge cant exist!";

    system("pause");
    return 0;

}