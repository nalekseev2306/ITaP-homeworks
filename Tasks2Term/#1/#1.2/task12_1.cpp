#include <iostream>
#include <algorithm>
#include <list>
#include <set>
#include <string>

using namespace std;

// создаём последовательность вручную
list<int> makeSeq() {
    string str;
    list<int> seq;
    getline(cin, str);
    str += ' ';
    while(str != "") {
        string buf = str.substr(0, str.find_first_of(' '));
        seq.push_back(stoi(buf));
        str.erase(str.begin(), str.begin() + str.find_first_of(' ') + 1);
    }
    return seq;
}

// находим уникальный цифры в числе
set<int> getDigits(int n) {
    set<int> digits;
    while(n != 0) {
        digits.insert(n % 10);
        n /= 10;
    }
    return digits;
}

int main() {

    cout << "Enter sequence: ";
    list<int> numbers = makeSeq();
    set<int> goodDigits, badDigits, res;

    // ищем уникальные цифры в трёхзначных и других числах
    for(int num: numbers) {
        set<int> tmp = getDigits(num);
        if(num >= 100 && num <= 999) badDigits.insert(tmp.begin(),  tmp.end());
        else goodDigits.insert(tmp.begin(),  tmp.end());
    }
    set_difference(goodDigits.begin(), goodDigits.end(), badDigits.begin(), badDigits.end(), inserter(res, res.begin()));

    cout << "Answer: ";
    for(int d: res) {
        cout << d << ' ';
    }
    cout << endl;

    system("pause");
    return 0;

}