#include <iostream>
#include <cmath>

using namespace std;

int main() {

float x, y; // вводим переменные
cout << "Enter X = ";
cin >> x; // задаём значение
cout << "Enter Y = ";
cin >> y; // задаём значение

long double ans = ((sqrt(exp(x*x + y*y)) - y*x) / (x*x + y*y)) / 2.0 + log(sqrt(pow(x, 4)) / sqrt(pow(y, 4))); // составляем выражение
cout << "Answer: " << ans << endl; // выводим ответ

system("pause");
return 0;

}
