#include <iostream>

using namespace std;

long long fibonachirec(int n) { // находит n-ое число Фибоначи рекурсивно
    if(n == 1 || n == 2) return 1;
    return fibonachirec(n-2) + fibonachirec(n-1);
}

long long fibonachi(int n) { // находит n-ое число Фибоначи циклично
    int a1 = 1, a2 = 1, cur;
    if(n <= 2) return 1;
    else {
        for(int i{2}; i < n; i++) {
            cur = a1 + a2;
            a1 = a2;
            a2 = cur;
        }
        return cur;
    }
}

int main() {

    int n;
    cout << "Input number: ";
    cin >> n;

    cout << fibonachirec(n) << " or " << fibonachi(n) << endl;

    system("pause");
    return 0;
    
}