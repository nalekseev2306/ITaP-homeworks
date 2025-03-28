#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n, max{-100000};

cout << "Enter array lenght: ";
cin >> n;
int *arr = new int[n];

cout << "Array: ";
for(int i{0}; i < n; i++) { // заполняем массив случайными числами и выводим его
    arr[i] = rand() % 10;
    cout << arr[i] << " ";
    if((arr[i] % 2 == 0) && (arr[i] > max)) max = arr[i]; // ищем максимальный чётный элемент 
}

cout << endl << "Elements: ";
if(max > -100000) { // если нашёлся такой элемент
    for(int i{0}; i < n; i++) { // проверяем каждый елемент массива на условие и выводим номер
        if(arr[i] == max) {
            cout << i << " ";
        }
    }
}

else cout << "no elements!"; // если не нашлось елементов по условию

cout << endl;
delete [] arr;
system("pause");
return 0;

}