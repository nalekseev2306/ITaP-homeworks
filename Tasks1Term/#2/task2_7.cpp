#include <iostream>
#include <cmath>

using namespace std;

int main() {

float x;

cout << "Enter X: "; // задаём число х
cin >> x;

// проводим проверку 
if((x + 5) < 0) {
    cout << "Root of a negative number" << endl;
}
else if((8 - 2 * x) < 0) {
    cout << "Logarithm of a non-positive number" << endl;
}
else if((x*x + 2 * x + 1) == 0) {
    cout << "Division by zero" << endl;
}
else {
    cout << "Answer: " << (sqrt(x + 5) + log(8 - 2 * x)) / sqrt(x*x + 2 * x + 1) << endl;
}

system("pause");
return 0;

}
