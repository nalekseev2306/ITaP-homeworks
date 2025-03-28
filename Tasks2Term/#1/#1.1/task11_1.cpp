#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

vector<int> makeVector(int n) { // создаём вектор со случайными элементами
    srand(time(0));
    vector<int> newVec;
    for(int i{0}; i < n; i++) {
        newVec.push_back(rand() % 21);
    }
    return newVec;
}

void printVector(vector<int> vec) { // выводим вектор в терминал
    for(auto it = vec.begin(); it < vec.end(); it++) {
        cout << *it << ' ';
    }
    cout << endl;
}

int main() {

    int n;
    cout << "Enter lenght of vector: ";
    cin >> n;

    vector<int> vec = makeVector(n);
    cout << "Start vector: ";
    printVector(vec);

    // стираем перенесённые в конец нечётные элементы
    vec.erase(remove_if(vec.begin(), vec.end(), [](int elem){return elem % 2 != 0;}), vec.end());
    cout << "New vector: ";
    printVector(vec);
    
    system("pause");
    return 0;

}