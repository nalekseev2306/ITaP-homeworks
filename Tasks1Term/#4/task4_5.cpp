#include <iostream>
#include <cmath>

using namespace std;

int main() {

float y1{2}, y2{1}, y, n;

cout << "Enter n: ";
cin >> n;

cout << "y1 = " << y1 << endl;
cout << "y2 = " << y2 << endl;

for(int i{3}; i <= n; i++) {
    
    y = (y2 / 2 + y1 / 3) / 3; // состовляем слудующий член последовательности
    y1 = y2; // сдвигаем члены последовательности на предыдущий и текущий
    y2 = y;

    cout << "y" << i << " = " << y << endl;

}

system("pause");
return 0;

}