#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n, cnt{0};
cout << "Enter size of matrix: ";
cin >> n;

cout << "Start array:" << endl;
int **arr = new int*[n]; // создаём двумерный массив
for(int i{0}; i < n; i++) {
    arr[i] = new int[n];
}
for(int i{0}; i < n; i++) { // заполняем массив и выводим
    for(int j{0}; j < n; j++) {
        arr[i][j] = rand() % 10;
        cout << arr[i][j] << "  ";
    }
    cout << endl;
}

cout << "Final array:" << endl; // выводим массив по новым правилам
for(int i{0}; i < n; i++) {
    for(int j{0}; j < n; j++) {
        for(int o{0}; o < n; o++) {
            if(arr[o][j] % 2 == 0) {cnt++;}
        } 
        if(cnt == n) {
            cout << arr[i][j] << "  "; // если весь столбец состоит из четных чисел дублируем элемент
        }
        cout << arr[i][j] << "  "; 
        cnt = 0;
    }
    cout << endl;
}

for(int i{0}; i < n; i++) { // удаление двумерного массива
    delete [] arr[i];
}
delete [] arr;
system("pause");
return 0;

}