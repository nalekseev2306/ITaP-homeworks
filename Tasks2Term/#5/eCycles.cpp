#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// задаём список смежности (через пробел)
vector<vector<int>> adjList;

void makeAdjList(int vert) {
    adjList.resize(vert);

    for (int i = 0; i < vert; i++) {
        string str;
        cout << "Vertex " << i << ": ";
        cin.clear();
        cin.sync();
        getline(cin, str);

        if (str == "") continue;
        while (str.find(" ") != -1) {
            int buf = stoi(str.substr(0, str.find(" ")));
            if (buf < vert && buf != i) adjList[i].push_back(buf);
            str.erase(str.begin(), str.begin() + str.find(" ") + 1);
        }

        adjList[i].push_back(stoi(str));
        sort(adjList[i].begin(), adjList[i].end());
        adjList[i].erase(unique(adjList[i].begin(), adjList[i].end()), adjList[i].end());
    }

}

// удаляем ребро
void delEdge(int x, int y) {
    adjList[x].pop_back();
    for (auto it = adjList[y].begin(); it != adjList[y].end(); it++) {
        if (*it == x) {
            adjList[y].erase(it);
            break;
        }
    }
}

// ищем Эйлеров цикл
vector<int> path;
vector<int> eCycle() {
    vector<int> res;
    int v1 = -1, v2 = -1;

    // проверяем степени вершин
    for (int i = 0; i < adjList.size(); i++) {
        if (adjList[i].size() % 2 != 0) {
            if (v1 == -1) v1 = i;
            else if (v2 == -1) v2 = i;
            else return {};
        }
    }

    // добавляем мнимое ребро
    if (v1 != -1) {
        adjList[v1].push_back(v2);
        adjList[v2].push_back(v1);
    }

    stack<int> st;
    st.push(v1 != -1 ? v1: 0);

    while (!st.empty()) {
        int h = st.top();
        if (!adjList[h].empty()) {
            int x = adjList[h].back();
            delEdge(h, x);
            st.push(x);
        }
        else {
            res.push_back(h);
            st.pop();
        }
    }

    // составляем путь
    if (v1 != -1) {
        for (int i = 0; i + 1 < res.size(); i++) {
            if ((res[i] == v1 && res[i+1] == v2) || 
                (res[i] == v2 && res[i+1] == v1)) {
                    path.insert(path.end(), res.begin() + i + 1, res.end());
                    path.insert(path.end(), res.begin() + 1, res.begin() + i + 1);
                    break;
                }
        }
    }

    // проверяем на отсутсвие рёбер
    for (auto edges: adjList) {
        if (!edges.empty()) {
            cout << "Euler cycle is missing!" << endl;
            return {};
        }
    }

    return path;
}

int main() {

    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    makeAdjList(n);

    // 1 2 4 5
    // 0 4 3
    // 0 4 3
    // 1 2 4 5
    // 0 1 2 3
    // 0 3
    
    eCycle();
    cout << "Euler path/cycle: ";
    for (int vert: path) {
        cout << vert << " ";
    }
    cout << endl;

    system("pause");
    return 0;

}