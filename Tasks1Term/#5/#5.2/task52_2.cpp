#include <iostream>

using namespace std;

int main() {

int n;
cout << "Enter size of matrix: ";
cin >> n;
int **arr = new int*[n];

cout << "Start array:" << endl;
for(int i{0}; i < n; i++) { // создаем и выводим двумерный массив
    arr[i] = new int[n];
}
for(int i{0}; i < n; i++) {
    for(int j{0}; j < n; j++) {
        arr[i][j] = j + 1;
        cout << arr[i][j] << "  "; 
    }
    cout << endl;
}

for(int i{0}; i < n; i++) { // меняем местами элемнты в каждой строке
    for(int j{1}; j < n; j += 2) {
        swap(arr[i][j], arr[i][j-1]);
    }
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