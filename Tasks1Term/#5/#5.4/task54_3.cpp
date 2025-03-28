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
for(int i{0}; i < n; i++) { // заполняем массив псевдослучайными числами и выводим его
    arr[i] = rand() % 19;
    cout << arr[i] << " "; 
}

cout << endl << "Finish array: ";
for(int i{0}; i < n; i++) { // проверяем каждый элемент массива на четность
    if(arr[i] % 2 != 0) {
        cout << arr[i] << " ";
    }
}
cout << endl;

delete [] arr;
system("pause");
return 0;

}