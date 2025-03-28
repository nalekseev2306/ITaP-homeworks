#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n;

cout << "Enter array lenght: ";
cin >> n;
int *arr = new int[n];

cout << "Start array: ";
for(int i{0}; i < n; i++) { // заполняем массив случайными числами и выводим его
    arr[i] = rand() % 10;
    cout << arr[i] << " ";
}

cout << endl;
if(n % 2 == 0) {
    swap(arr[n / 2], arr[n / 2 - 1]); // меняем два средних элемента
}
else {
    swap(arr[0], arr[n / 2]); // меняем первый и средний
}

cout << "Final array: ";
for(int i{0}; i < n; i++) { // выводим новый массив
    cout << arr[i] << " ";
}

cout << endl;
delete [] arr;
system("pause");
return 0;

}