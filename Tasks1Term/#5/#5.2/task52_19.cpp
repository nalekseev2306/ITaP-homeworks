#include <iostream>

using namespace std;

int main() {

int n;
cout << "Enter size of matrix: ";
cin >> n;
int **arr = new int*[n];

cout << "Array:" << endl;
for(int i{0}; i < n; i++) { // создаем и выводим двумерный массив
    arr[i] = new int[n];
}
for(int i{0}; i < n; i++) { // заполняем массив змейкой
    for(int j{0}; j < n; j++) {
        if(j % 2 == 0) arr[i][j] = j * n + i; 
        else arr[i][j] = (j+1)*n - i - 1;
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