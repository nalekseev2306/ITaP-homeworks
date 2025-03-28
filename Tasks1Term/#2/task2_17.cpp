#include <iostream>
#include <algorithm> 
#include <cmath>

using namespace std;

int main() {

const double eps = 1e-4;
float a, b, c, p, s, r, R, h, med;
string type;

cout << "Enter first side: ";
cin >> a;
cout << "Enter second side: ";
cin >> b;
cout << "Enter third side: ";
cin >> c;

float arr[] = {a, b, c}; 
sort(begin(arr), end(arr)); // отсортированный массив трех сторон

if(arr[0] + arr[1] > arr[2]) { // треугольник существует

    p = (a + b + c) / 2; // полупериметр
    s = sqrt(p * (p - a) * (p - b) * (p - c)); // площадь
    r = s / p; // радиус вписанной окружноси
    R = (a * b * c) / (4 * s); // радиус описанной окружности
    cout << "S = " << s << "\nr = " << r << "\nR = " << R << endl;

    if(abs(arr[0] - arr[2]) < eps) { // проверка на равносторонний треугольник
        type = "equilateral"; // вид треугольника
        h = r * 3; // высота
        med = h; // медиана
        cout << "Type triangle: " << type << "\nh = " << h << "\nmediana = " << med << endl;
    }

    else if(abs(arr[0] - arr[1]) < eps) { // проверка на равнобедренный треугольник с меньшими сторонами
    
        if(abs((arr[0]*arr[0] + arr[1]*arr[1]) - arr[2]*arr[2]) < eps) { // проверка на прямоугольный треугольник
            type = "isosceles and right"; 
            h = (2 * s) / arr[2];
            med = arr[2] / 2;
            cout << "Type triangle: " << type << "\nCatets: " << arr[0] << " and " << arr[1] << "\nHypotenuse: " << arr[2];
            cout << "\nh = " << h << "\nmediana = " << med << endl;
        }
        else { 
            type = "isosceles";
            h = (2 * s) / arr[2];
            med = h;
            cout << "Type triangle: " << type << "\nSides: " << arr[0] << " and " << arr[1] << "\nBase: " << arr[2];
            cout << "\nh = " << h << "\nmediana = " << med << endl;
        }
    }

    else if(abs(arr[1] - arr[2]) < eps) { // проверка на равнобедрянный треугольник с бОльшими сторонами
        type = "isosceles";
        h = (2 * s) / arr[0];
        med = h;
        cout << "Type triangle: " << type << "\nSides: " << arr[1] << " and " << arr[2] << "\nBase: " << arr[0];
        cout << "\nh = " << h << "\nmediana = " << med << endl;
    }

    else if(abs((arr[0]*arr[0] + arr[1]*arr[1]) - arr[2]*arr[2]) < eps) { // проверка на прямоугольный треугольник
        type = "right"; 
        h = (2 * s) / arr[2];
        med = arr[2] / 2;
        cout << "Type triangle: " << type << "\nCatets: " << arr[0] << " and " << arr[1] << "\nHypotenuse: " << arr[2];
        cout << "\nh = " << h << "\nmediana = " << med << endl;
    }

    else { // разносторонний треугольник
        type = "scalene"; 
        cout << "Type triangle: " << type << endl;
    }
}
else { // треугольник не существует
    cout << "Degenerate triangle!" << endl; 
}

system("pause");
return 0;

}