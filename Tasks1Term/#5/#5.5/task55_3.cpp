#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n, y, x;
bool flag = false;
cout << "Enter size of matrix: ";
cin >> n;
cout << "Enter number y: ";
cin >> y;
cout << "Enter row x: ";
cin >> x;

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
        cout << arr[i][j] << "  ";
        if(arr[i][j] == y) flag = true; // нашли y в строке
    }
    if(flag) {
        cout << endl;
        for(int o{0}; o < n; o++) {
            cout << x << "  ";
        }
        flag = false;
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