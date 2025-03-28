#include <iostream>

using namespace std;

int main() {

int a, b, k;
cout << "Enter dividend: "; // делимое
cin >> a;
cout << "Enter divisor: "; // делимое
cin >> b;

for(int i = 1; i * b <= a; i++) k = i;  // найдём сколько целых b входит в число a

cout << "a / b = " << k << endl; // целая часть числа
cout << "a % b = " << a - (k * b) << endl; // остаток числа

system("pause");
return 0;

}