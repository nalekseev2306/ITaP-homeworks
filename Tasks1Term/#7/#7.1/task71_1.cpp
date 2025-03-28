#include <iostream>
#include <string>

using namespace std;

// Дана строка, содержащая латинские буквы. Все гласные буквы заменить пробелом.

string task1(string str) { // заменяем гласные буквы на пробелы
    string alph = "EeYyUuIiOoAa";
    for(int i{0}; i < str.length(); i++) {
        if(alph.find(str[i]) != -1) {
            str[i] = ' ';
        }
    }
    return str;
}

int main() {

    string str;
    cout << "Enter string: ";
    getline(cin, str);

    cout << "Task 1: " << task1(str) << endl;

    system("pause");
    return 0;

}