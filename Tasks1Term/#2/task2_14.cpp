#include <iostream>
#include <cmath>

using namespace std;

int main() {

char choice;
float a, b, c, r, p;
const float pi = 3.14; // число пи

cout << "Circle - c, Square - s, Triangel - t, Rectangel - r" << endl;
cout << "Make your chose: ";
cin >> choice;

switch(choice) {
    case 'c': // круг
        cout << "Enter radius: ";
        cin >> r;
        cout << "S = " << pi * r*r << endl;
        cout << "P = " << 2 * pi * r << endl;
        break;
    case 's': // квадрат
        cout << "Enter lenght: ";
        cin >> a;
        cout << "S = " << a*a << endl;
        cout << "P = " << 4 * a << endl;
        break;
    case 't': // треугольник
        cout << "Enter first side: ";
        cin >> a;
        cout << "Enter second side: ";
        cin >> b;
        cout << "Enter third side: ";
        cin >> c;
        if((a + b > c) && (a + c > b) && (b + c > a)) {
            p = (a + b + c) / 2;
            cout << "S = " << sqrt(p * (p - a) * (p - b) * (p - c)) << endl;
            cout << "P = " << a + b + c << endl;
        }
        else cout << "Degenerate triangle!" << endl;
        break;
    case 'r': // прямоугольник
        cout << "Enter lenght: ";
        cin >> a;
        cout << "Enter width: ";
        cin >> b;
        cout << "S = " << a * b << endl;
        cout << "P = " << 2 * (a + b) << endl;
        break;
    default:
        cout << "Uncorrect choice!" << endl;
}

system("pause");
return 0;

}
