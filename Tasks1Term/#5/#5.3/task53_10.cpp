#include <iostream>

using namespace std;

int main() {

int n, m;
cout << "Enter length of polynomial P(x): ";
cin >> n;
cout << "Enter length of polynomial Q(x): ";
cin >> m;

int *p = new int[++n]; // создаём полином P(x) из треугольника паскаля
p[0] = 1;
cout << "P(x) = " << p[0];
for(int i{1}; i < n; i++) {
    p[i] = p[i-1] * (n-i) / i;
    cout << " " << p[i];
}
cout << endl;

int *q = new int[++m]; // создаём полином Q(x) из треугольника паскаля
q[0] = 1;
cout << "Q(x) = " << q[0];
for(int i{1}; i < m; i++) {
    q[i] = q[i-1] * (m-i) / i;
    cout << " " << q[i];
}
cout << endl;

int *a = new int[n+m-1]; // создаём полином P(x)*Q(x)
for(int i{0}; i < n+m-1; i++) {
    a[i] = 0;
}
for(int i{0}; i < n; i++) {
    for(int j{0}; j < m; j++) {
        a[i+j] += p[i] * q[j];
    }
}

int *b = new int[n+m-2]; // создаём полином производной от P(x)*Q(x)
cout << "(P(x)*Q(x))' = ";
for(int i{1}; i < n+m+1; i++) {
    b[i-1] = a[i] * i;
}

for(int i{0}; i < n+m-2; i++) { // выводим итоговый полином
    cout << b[i] << " ";
}
cout << endl;

delete [] p;
delete [] q;
delete [] a;
delete [] b;
system("pause");
return 0;

}

// 1 3 3 1    1 2 1
// 1 3 3 1
//   2 6 6 