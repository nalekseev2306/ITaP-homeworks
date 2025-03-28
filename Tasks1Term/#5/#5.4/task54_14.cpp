#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n, x;
cout << "Enter array lenght: ";
cin >> n;
cout << "Enter x: ";
cin >> x;
int *arr = new int[n];

cout << "Start array: ";
for(int i{0}; i < n; i++) { // заполняем массив и выводим его
    arr[i] = rand() % 10;
    cout << arr[i] << " ";
}

cout << endl << "Finish array: ";
for(int i{0}; i < n; i++) { // проверяем элементы массива на условие и выводим 
    if(arr[i] % 2 != 0) { // выводим x перед нечётными
        cout << x << " ";
    }
    cout << arr[i] << " ";
}

cout << endl;
delete [] arr;
system("pause");
return 0;

}