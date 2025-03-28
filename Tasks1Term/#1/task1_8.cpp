#include <iostream>
#include <cmath>

using namespace std;

int main() {

float x, y; // вводим переменные
cout << "Enter X = ";
cin >> x; // задаём значение
cout << "Enter Y = ";
cin >> y; // задаём значение

long double ans = sqrt((sqrt(cos(x) + sin(y)) + exp(x + y)) / (sqrt(x + y + log(x)*log(x)))); // составляем выражение
cout << "Answer: " << ans << endl;

system("pause");
return 0;

}