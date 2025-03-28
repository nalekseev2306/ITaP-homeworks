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

vector<int> concatenate(vector<int> a, vector<int> b) { // сортировка слиянием (только для отсортированных векторов)
    vector<int> newVec;
    auto aIt = a.begin(), bIt = b.begin();
    while(aIt != a.end() && bIt != b.end()) {
        if(*aIt <= *bIt) {
            newVec.push_back(*aIt);
            aIt++;
        }
        else if(*aIt >= *bIt) {
            newVec.push_back(*bIt);
            bIt++;
        }
    }
    if(aIt == a.end()) newVec.insert(newVec.end(), bIt, b.end());
    else newVec.insert(newVec.end(), aIt, a.end());
    return newVec;
}

int main() {

    int n, x;
    cout << "Enter lenght of first vector: ";
    cin >> n;
    cout << "Enter X: ";
    cin >> x;

    // выполняем действия над первым вектором
    vector<int> vec1 = makeVector(n);
    cout << "Start vector1: ";
    printVector(vec1);
    vec1.erase(remove_if(vec1.begin(), vec1.end(),[x](int elem){return elem % x == 0;}), vec1.end()); // стираем элементы кратные х
    cout << "New vector1: ";
    printVector(vec1);

    int a, b, y;
    cout << endl << "Enter lenght of second vector: ";
    cin >> n;
    cout << "Enter replacement range [a, b]: ";
    cin >> a >> b;
    cout << "Enter replacement Y: ";
    cin >> y;

    // выполняем действия над вторым вектором
    vector<int> vec2 = makeVector(n); // инициализируем второй вектор
    cout << "Start vector2: ";
    printVector(vec2);
    replace_if(vec2.begin(), vec2.end(), [a, b](int elem){return elem >= a && elem <= b;}, y);
    cout << "New vector2: ";
    printVector(vec2);

    // сортируем вектора
    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());
    cout << endl << "Sorted vector1: ";
    printVector(vec1);
    cout << "Sorted vector2: ";
    printVector(vec2);

    // объединяем вектора
    cout << endl << "Concatenated vector: ";
    printVector(concatenate(vec1, vec2));
    
    system("pause");
    return 0;

}