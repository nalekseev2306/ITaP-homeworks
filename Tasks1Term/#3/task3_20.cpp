#include <iostream>

using namespace std;

int main() {

int a, n;
cout << "Enter number of steps: ";
cin >> a;
cout << endl;

for(int i = 1; i <= a; i++) { // состовляем а ступенек
    n = i * 2;

    for(int j = 1; j <= i; j++, n -= 2) { // состовляем первую строку ступеньки
        cout << n << " ";
    }
    cout << endl;

    for(int j = 1; j <= i; j++) { // состовляем вторую строку ступеньки
        cout << (i - 1) * 3 << " ";
    }
    cout << endl;
}

system("pause");
return 0;
    
}