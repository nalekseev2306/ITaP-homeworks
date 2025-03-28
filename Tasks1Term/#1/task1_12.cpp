#include <iostream>

using namespace std;

int main() {

int x;
cout << "Enter X = ";
cin >> x;

int a, b, c; // цифры числа x
a = x / 100;
b = (x / 10) % 10;
c = x % 10;

int num1, num2, num3; // цифры числа y
num1 = 25 % a;
num2 = 25 % b;
num3 = 25 % c;

int y = 100 * num1 + 10 * num2 + num3; // составляем число y
cout << "Y = " << y << endl;

system("pause");
return 0;

}