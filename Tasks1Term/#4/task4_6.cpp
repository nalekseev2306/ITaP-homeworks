#include <iostream>
#include <cmath>

using namespace std;

int main() {

int n{10}, cnt{0};
float x, eps{0.01};

cout << "Enter x: ";
cin >> x;

float a{1}, s{a}; // следующий член и сумма

for(int i{1}; abs(a) > eps && i <= n; i++) {
    float d = x / i;

    if (abs(a) < abs(a * d)) {
        cnt++;
    }

    a *= d; // каждый следующий член определяем рекурентным соотношением, т.е. предыдущий член умножаем на d
    s += a; // сумма ряда

}

if(cnt < n/2) cout << "e^x = " << exp(x) << "  " << "S = " << s << endl;
else cout << "The sequence diverges!" << endl; // последовательность расходится

system("pause");
return 0;

}