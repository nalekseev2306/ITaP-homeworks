#include <iostream>

using namespace std;

template <typename T>
T **create(T b, int n, int m) { // создание массива
    T **arr = new T*[n]; // выделяем память
    for(int i{0}; i < n; i++) {
        arr[i] = new T[m];
    }
    for(int i{0}; i < n; i++) { // задаём значения массива
        for(int j{0}; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    return arr;
}

template <typename T>
void print(T **arr, int n, int m) { // вывод массива
    for(int i{0}; i < n; i++) {
        for(int j{0}; j < m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

template <typename T>
void delarr(T **arr, int n) { // удаление двумерного массива
    if(n > 1) {
        for(int i{0}; i < n; i++) { 
            delete [] arr[i];
        }
        delete [] arr;
    }
}

template <typename T>
void change(T **arr, int n, int m) { // меняем первую строку с последней, вторую с предпоследней и тд
    for(int i{0}; i < n/2; i++) {
        swap(arr[i], arr[n-1-i]);
    }
}

int main() {

int n, m;
char c;
cout << "Enter size of matrix:" << endl;
cin >> n >> m;

do {
    int k;
    cout << "Chose type: \n1 - int \n2 - double \n3 - float \n4 - char" << endl;
    cin >> k;

    switch(k) {
        case 1: {
            int b{1};
            cout << "Enter elements of array:" << endl;
            int **arr = create(b, n, m);
            cout << "INT Array: " << endl;
            print(arr, n, m);
            change(arr, n, m);
            cout << "FINAL Array: " << endl;
            print(arr, n, m);
            // delarr(arr, n);
            break;
        }
        case 2: {
            double b{1};
            cout << "Enter elements of array:" << endl;
            double **arr = create(b, n, m);
            cout << "DOUBLE Array: " << endl;
            print(arr, n, m);
            change(arr, n, m);
            cout << "FINAL Array: " << endl;
            print(arr, n, m);
            // delarr(arr, n);
            break;
        }
        case 3: {
            float b{1};
            cout << "Enter elements of array:" << endl;
            float **arr = create(b, n, m);
            cout << "FLOAT Array: " << endl;
            print(arr, n, m);
            change(arr, n, m);
            cout << "FINAL Array: " << endl;
            print(arr, n, m);
            // delarr(arr, n);
            break;
        }
        case 4: {
            char b{' '};
            cout << "Enter elements of array:" << endl;
            char **arr = create(b, n, m);
            cout << "CHAR Array: " << endl;
            print(arr, n, m);
            change(arr, n, m);
            cout << "FINAL Array: " << endl;
            print(arr, n, m);
            // delarr(arr, n);
            break;
        }
        default: cout << "Input ERROR!" << endl;
    }
    cout << "Continue? y - yes   n - no: ";
    cin >> c;
}
while(c != 'n');

system("pause");
return 0;

}