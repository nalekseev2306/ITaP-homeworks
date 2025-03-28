#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n, min{100000}, max{-100000}, min_i, max_i;
cout << "Enter size of matrix: ";
cin >> n;
int **arr = new int*[n];

cout << "Start array:" << endl;
for(int i{0}; i < n; i++) { // создаем и выводим двумерный массив
    arr[i] = new int[n];
}
for(int i{0}; i < n; i++) {
    for(int j{0}; j < n; j++) {
        arr[i][j] = rand() % 10;
        if(arr[i][j] > max) { // мщем первое максимальное число в строке
            max = arr[i][j];
            max_i = i;
        }
        else if(arr[i][j] < min) { // ищем первое минимальное число в строке
            min = arr[i][j];
            min_i = i;
        } 
        cout << arr[i][j] << "  "; 
    }
    cout << endl;
}

for(int j{0}; j < n; j++) { // меняем строки местами
    swap(arr[max_i][j], arr[min_i][j]);
}

cout << "Final array:" << endl;
for(int i{0}; i < n; i++) { // выводим новый массив
    for(int j{0}; j < n; j++) {
        cout << arr[i][j] << "  "; 
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