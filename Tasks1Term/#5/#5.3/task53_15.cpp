#include <iostream>

using namespace std;

int main() {

int n;
cout << "Enter n: ";
cin >> n;

if(n >= 2) {

    int **a = new int*[n]; // создаём двумерный массив
    for(int i{0}; i < n; i++) {
        a[i] = new int[i+1];
    }
    a[0][0] = a[1][0] = a[1][1] = 1; // задаем значения первых двух строк

    for(int i{2}; i < n; i++) { // заполняем по правилу составления треугольника паскаля
        a[i][0] = 1;
        for(int j{1}; j < i; j++) {
            a[i][j] = a[i-1][j-1] + a[i-1][j];
        }
        a[i][i] = 1;
    }

    for(int i{0}; i < n; i++) { // выводим треугольник графически
        for(int j{0}; j < i+1; j++) {
            if(a[i][j] % 2 != 0) {
                cout << "#";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }

    for(int i{0}; i < n; i++) { // удаление двумерного массива
    delete [] a[i];
    }
    delete [] a;

}

system("pause");
return 0;

}