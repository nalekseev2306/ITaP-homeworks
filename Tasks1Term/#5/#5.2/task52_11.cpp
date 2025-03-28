#include <iostream>
#include <time.h>

using namespace std;

int main() {

srand(time(0));
int n, k{0};
float sum{0};
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
        cout << arr[i][j] << "  "; 
    }
    cout << endl;
}

for(int i{0}; i < n; i++) {
    for(int j{0}; j < n; j++) {
        if((j <= n-i-1 && j <= i) || (j >= i && j >= n-i-1)) { // проверяем находится ли элемент в области
            if(arr[i][j] % 2 != 0) { // проверяем на нечётность
                sum += arr[i][j];
                k++;
            }
        }
    }
}

if(k > 0) cout << "Arithmetic mean of elements: " << sum / k << endl; // находим среднее арифметическое элементов
else cout << "No odd elements!";

for(int i{0}; i < n; i++) { // удаление двумерного массива
    delete [] arr[i];
}
delete [] arr;
system("pause");
return 0;

}