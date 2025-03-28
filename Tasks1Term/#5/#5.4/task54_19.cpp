#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n, x, y;
cout << "Enter array lenght: ";
cin >> n;
cout << "Enter x: ";
cin >> x;
cout << "Enter y: ";
cin >> y;

int *arr = new int[n];
cout << "Start array: ";
for(int i{0}; i < n; i++) { // заполняем массив и выводим его
    arr[i] = rand() % 10;
    cout << arr[i] << " ";
}

cout << endl << "Finish array: ";
for(int i{0}; i < n; i++) { // проверяем элементы массива на условие и выводим 
    if(arr[i] == x) { // выводим x перед нечётными
        cout << y << " ";
    }
    cout << arr[i] << " ";
}

cout << endl;
delete [] arr;
system("pause");
return 0;

}