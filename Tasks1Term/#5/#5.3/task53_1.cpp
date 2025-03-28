#include <iostream>

using namespace std;

int main() {

int n;
cout << "Enter length of polynomial P(x): ";
cin >> n;

int *a = new int[++n]; // создаём полином из треугольника паскаля
a[0] = 1;
cout << "P(x) = " << a[0];
for(int i{1}; i < n; i++) {
    a[i] = a[i-1] * (n-i) / i;
    cout << " " << a[i];
}
cout << endl;

int *b = new int[n-1]; // вычисляем полином производной P(x)
cout << "P(x)' = "; 
for(int i{1}; i < n; i++) {
   b[i-1] = a[i] * i;
}

for(int i{0}; i < n-1; i++) { // выводим новый полином
    cout << b[i] << " ";
}
cout << endl;

delete [] a;
delete [] b;
system("pause");
return 0;

}
