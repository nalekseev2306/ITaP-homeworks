#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

vector<vector<pair<int, int>>> graph;

// создаём неориентированный взвешенный граф
void makeGraph(const string& fileName) {
    ifstream file(fileName);

    string line;
    getline(file, line);
    istringstream iss(line);

    int n;
    iss >> n;
    graph.resize(n);

    while (getline(file, line)) {
        istringstream iss(line);

        int x, y, w;
        iss >> x >> y >> w;

        if (x < n && y < n) {
            graph[x].push_back({y, w});
            graph[y].push_back({x, w});
        }
    }

}

// алгоритм Дейкстры
void dijkstraAlg(int start, vector<int>& dist, vector<int>& prev) {
    dist.resize(graph.size(), INT_MAX);
    prev.resize(graph.size(), -1);
    dist[start] = 0;

    queue<pair<int, int>> q;
    q.push({start, 0});

    while (!q.empty()) {
        int c = q.front().first;
        int d = q.front().second;
        q.pop();

        if (d > dist[c]) continue;

        for (auto edge : graph[c]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[v] > dist[c] + w) {
                dist[v] = dist[c] + w;
                prev[v] = c;
                q.push({v, dist[v]});
            }
        }
    }
}

// восстанавливаем путь
stack<int> getPath(int end, vector<int>& prev) {
    stack<int> path;
    for (int i = end; i != -1; i = prev[i])
        path.push(i);
    return path;
}

int main() {

    makeGraph("data.txt");

    int start;
    vector<int> dist, prev;

    cout << "Enter start vertex: ";
    cin >> start;

    dijkstraAlg(start, dist, prev);
    
    for (int i = 0; i < graph.size(); i++) {
        if (i == start) continue;
        cout << "Vertex " << i << ": " << "Distantion = " << dist[i];
        cout << ", Path = ";
        stack<int> path = getPath(i, prev);
        while (!path.empty()) {
            cout << path.top() << " ";
            path.pop();
        }
        cout << endl;
    }

    system("pause");
    return 0;

}