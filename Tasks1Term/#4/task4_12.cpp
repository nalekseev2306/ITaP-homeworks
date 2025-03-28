#include <iostream>
#include <cmath>

using namespace std;

int main() {

int n{10}, cnt{0};
float x, eps{0.001};

cout << "Enter x: ";
cin >> x;

float a{-x*x*x / 6}, s{x + a}; // первый член и сумма

for(int i{2}; abs(a) > eps && i <= n; i++) {
    float d = -x*x / (2 * i * (2 * i + 1));

    if (abs(a) < abs(a * d)) { 
        cnt++;
    }  

    a *= d; // каждый следующий член определяем рекурентным соотношением, т.е. предыдущий член умножаем на d
    s += a; // сумма ряда

}

if(cnt < n/2) cout << "sin(" << x << ") = " << sin(x) << "  " << "S = " << s << endl;
else cout << "The sequence diverges" << endl; // последовательность расходится

system("pause");
return 0;

}