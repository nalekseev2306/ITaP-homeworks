#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// рекурентное вычсление числа фибоначи
long long fib1(int n) {
    if (n <= 1) return n;

    long long prev = 0, cur = 1, tmp;

    for (int i = 1; i < n; i++) {
        tmp = cur;
        cur = cur + prev;
        prev = tmp;
    }

    return cur;
}

// вычисление числа фибоначи по формуле Бине (золоте сечение)
const double PHI = (1 + sqrt(5)) / 2;
const double THETA = (1 - sqrt(5)) / 2;
long long fib2(int n) {
    long double res = (pow(PHI, n) - pow(THETA, n)) / sqrt(5);
    return round(res);
}

// вычисление числа фибоначи через матрицу
void multiply(vector<vector<long long>> &p, vector<vector<long long>> m) {
    p = {
        {p[0][0] * m[0][0] + p[0][1] * m[1][0], p[0][0] * m[0][1] + p[0][1] * m[1][1]},
        {p[1][0] * m[0][0] + p[1][1] * m[1][0], p[1][0] * m[0][1] + p[1][1] * m[1][1]}
    };
}

void power(vector<vector<long long>> &p, int n) {
    if (n <= 1) return;
    
    vector<vector<long long>> m = {{1, 1}, {1, 0}};
    power(p, n/2);
    multiply(p, p);
    
    if (n%2 != 0) {
        multiply(p, m);
    }
}

long long fib3(int n) {
    if (n <= 1) return n;
    
    vector<vector<long long>> p = {{1, 1}, {1, 0}};
    power(p, n);
    return p[0][1];
}

template<typename Func>
void measure_time(Func f, int n, const string& name) {
    auto start = high_resolution_clock::now();
    long long res = f(n);
    auto end = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(end - start);
    
    cout << name << "(" << n << ") = " << res 
    << " - Time: " << dur.count() << " microsec" << endl;
}

int main() {

    int n;
    cout << "Enter n: ";
    cin >> n;
    
    measure_time(fib1, n, "iterativ"); // время выполнения O(n)
    measure_time(fib2, n, "gold"); // время выполнения О(1), но точность ограничена
    measure_time(fib3, n, "matrix"); // времявыполнения О(log n)

    system("pause");
    return 0;

}