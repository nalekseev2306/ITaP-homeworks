#include <iostream>

using namespace std;

int main() {

int n; 
cout << "Enter number: ";
cin >> n;

cout << "All prime numbers up to n: ";
cout << 2; // выводим 2, т.к. она является единственным четным простым числом

for(int i = 3; i <= n; i += 2) { // перебираем все нечётные числа до n
    bool flag = true;

    for(int j = 3; j * j <= i; j += 2) { // перебираем нечётные делители
        if(i % j == 0) {
            flag = false;
            break;
        }
    }

    if(flag) { // если в предыдущем цикле нашлось j кратное i, то переходим кследующему числу, иначе выводим простое число
        cout << ", " << i;
    }
}

cout << endl;
system("pause");
return 0;

}