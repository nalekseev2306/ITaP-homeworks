#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n, sum{0};

cout << "Enter array lenght: ";
cin >> n;
int *arr = new int[n];

cout << "Array: ";
for(int i{0}; i < n; i++) { // заполняем массив случайными числами и выводим его
    arr[i] = rand() % 10;
    cout << arr[i] << " ";
    if((i % 2 != 0) && (arr[i] % 2 != 0)) sum += arr[i]; // проверяем по условию и суммируем
}

cout << endl << "Sum of elements: " << sum << endl;

delete [] arr;
system("pause");
return 0;

}