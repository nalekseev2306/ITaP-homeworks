#include <iostream>
#include <cmath>

using namespace std;

// задание 11
int sum(int n) { // сумма от 1 до n
    if(n == 1) return 1;
    return n + sum(n-1);
}

double func11(int n, int i = 2) { // считаем выражение
    if(n < 1) return -1;
    if(n == 1) return 1;
    if(i == n) return sqrt(1 + i * sqrt(sum(n)));
    return sqrt(1 + i * func11(n, i + 1));
}

// задание 19
void print(int n, int a) { // отображение 1 элемента ёлочки
    for(int i{0}; i < a+1; i++) {
        for(int o{0}; o < n-i; o++) {
            cout << "  ";
        }
        for(int j{0}; j < 2*i+1; j++) {
            cout << "* ";
        }
        cout << endl;
    }
}

void tree(int n, int a = 1) { // генерируем ёлочку из n её элементов
    if(n <= 0) cout << "Input ERROR!";
    if(n >= a) {
        print(n, a);
        tree(n, a+1);
    }
}

int main() {

    int n, m;

    cout << "Input number for func: ";
    cin >> n;
    cout << func11(n) << endl;

    cout << "Input number for tree: ";
    cin >> m;
    tree(m);

    system("pause");
    return 0;
    
}