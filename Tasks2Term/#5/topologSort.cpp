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

vector<bool> used;
vector<int> parent;
vector<int> order;

void topologSort(int cur) {
    used[cur] = true;
    for (int i = 0; i < adjList[cur].size(); i++) {
        if (!used[adjList[cur][i]])
            topologSort(adjList[cur][i]); 
    }
    order.push_back(cur);
}

// проверяем на наличие цикла в графе
bool flag = false;
void dfsCycle(int start) {
    if (flag) return ;

    used[start] = true;

    for (auto cur: adjList[start]) {
        if (!used[cur]) {
            parent[cur] = start;
            dfsCycle(cur);
            if (flag) return ;
        } 
        else if (used[cur] == 1) {
            flag = true;
            return ;
        }
    }

    used[start] = false;
}

int main() {

    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    makeAdjList(n);
    used.resize(n, false);
    parent.resize(n, -1);

    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfsCycle(i);
    }

    if (!flag) {
        used.resize(n, false);
        for (int i = 0; i < n; i++) {
            if (!used[i])
                topologSort(i);
        }
    }
    else cout << "Graph has cycle!" << endl;
        
    // 0: 1 2
    // 1: 3 4 2
    // 2: 4 5
    // 3: 6
    // 4: 6
    // 5: 4 7
    // 6: 7 8
    // 7: 8
    // 8: 

    for (int vert : order) {
        cout << vert << ' ';
    }
    cout << endl;

    system("pause");
    return 0;

}