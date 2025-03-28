#include <iostream>

using namespace std;

int main() {

int a, x, y; // определяем переменные

// задаём значения переменным
cout << "Enter A: ";
cin >> a;
cout << "Enter X: ";
cin >> x;
cout << "Enter Y: ";
cin >> y;

int n1 = a / 100, n2 = (a / 10) % 10, n3 = a % 10; // цифры числа а
int sum = n1 + n2 + n3; // сумма цифр числа а

// задаём условия проверки
if((99 < a && a < 1000) && (-1 < x && x < 10) && (-1 < y && y < 10)) {
    if(sum % x == 0 && sum % y == 0) {
        n1 = abs(n1 - 5);
        n2 = abs(n2 - 5);
        n3 = abs(n3 - 5);
    }
    else if(sum % x == 0 && sum % y != 0) {
        n1 = (n1 * 2) % 10;
        n2 = (n2 * 2) % 10;
        n3 = (n3 * 2) % 10;
    }
    else if(sum % x != 0 && sum % y == 0) {
        n1 = (n1 + 1) % 10;
        n2 = (n2 + 1) % 10;
        n3 = (n3 + 1) % 10;
    }
    else {
        n1 = abs(n1 - 1);
        n2 = abs(n2 - 1);
        n3 = abs(n3 - 1);
    }
}
else {
    cout << "Input Error!" << endl;
    system("pause");
    return 0;
}

cout << "Answer: " << 100 * n1 + 10 * n2 + n3 << endl;

system("pause");
return 0;

}
