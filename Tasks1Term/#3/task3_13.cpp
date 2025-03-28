#include <iostream>
#include <cmath>

using namespace std;

int main() {

float a, b, h;
cout << "Enter left side: ";
cin >> a;
cout << "Enter right side: ";
cin >> b;
cout << "Enter step: ";
cin >> h;

for(float x = a; x <= b; x += h) { // перебираем все x в [a, b] с шагом h, проверяя по одз

    if((x*x - 1) <= 0) {
        cout << "x = " << x << ": " << "Logarithm of a non-positive number" << endl;
    }
    else if((x*x - 4*x + 4) < 0) {
        cout << "x = " << x << ": " << "Root of a negative number" << endl;
    }
    else if((x*x - 4*x + 4) == 0) {
        cout << "x = " << x << ": " << "Division by zero" << endl;
    }
    else {
        cout << "x = " << x << ": " << log(x*x - 1) / sqrt(x*x - 4*x + 4) << endl;
    }
}

system("pause");
return 0;

}