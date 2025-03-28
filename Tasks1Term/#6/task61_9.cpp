#include <iostream>

using namespace std;

int func9rec(int m, int n) { // количество комбинаций рекурсивное решение
    if(n == 0) return 1;
    if(n == m) return 1;
    return func9rec(m - 1, n - 1) + func9rec(m - 1, n);
}

int func9(int m, int n) { // количество комбинаций цикличное решение
    int cur, last = 1;
    if(m == 0) return 1;
    else {
        for(int i{1}; i < n+1; i++) { // представляем количество комбинаций в виде m-строки и n-элемента треугольника Паскаля
            cur = last * (m-i+1) / i;
            last = cur;
        }
        return cur;
    }
}

int main() {

    int m, n;
    cout << "Input two numbers: " << endl;
    cin >> m >> n;

    cout << func9rec(m, n) << " or " << func9(m, n) << endl;

    system("pause");
    return 0;
    
}