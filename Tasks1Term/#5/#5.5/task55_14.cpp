#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n, sum{0};
cout << "Enter size of matrix: ";
cin >> n;

cout << "Start array:" << endl;
int **arr = new int*[n]; // создаём двумерный массив
for(int i{0}; i < n; i++) {
    arr[i] = new int[n];
}
for(int i{0}; i < n; i++) { // заполняем массив и выводим
    for(int j{0}; j < n; j++) {
        arr[i][j] = rand() % 6;
        cout << arr[i][j] << "  ";
    }
    cout << endl;
}

cout << "Final array:" << endl; // выводим массив по новым правилам
for(int i{0}; i < n; i++) {
    for(int j{0}; j < n; j++) {
        sum += arr[i][j]; // ищем сумму всей строки
    }
    if(sum <= 9) { // если сумма однозначная - выводим строку
        for(int o{0}; o < n; o++) {
            cout << arr[i][o] << "  ";
        }
        cout << endl;
    }
    sum = 0; // обнуляем сумму
}

for(int i{0}; i < n; i++) { // удаление двумерного массива
    delete [] arr[i];
}
delete [] arr;
system("pause");
return 0;

}