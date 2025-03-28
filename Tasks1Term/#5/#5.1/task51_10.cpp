#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n;
bool flag = true;

cout << "Enter array lenght: ";
cin >> n;
int *arr = new int[n];

cout << "Array: ";
for(int i{0}; i < n; i++) { // заполняем массив случайными числами и выводим его
    arr[i] = rand() % 10;
    cout << arr[i] << " ";
}

cout << endl << "Elements: ";
for(int i{0}; i < n; i++) { // проверяем каждый елемент массива на условие и выводим номер
    if(arr[i] % 3 != 0) {
        flag = false;
        cout << i << " ";
    }
}

if(flag) cout << "no elements!"; // если не нашлось елементов по условию

cout << endl;
delete [] arr;
system("pause");
return 0;

}