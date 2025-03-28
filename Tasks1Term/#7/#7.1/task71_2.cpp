#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Дано предложение, содержащее знаки препинания. Поменять местами самое длинное и самое короткое слово.

vector<int> maxWord(string str) { // находим позицию и длинну самого длинного слова
    vector<int> res = {0, 0};
    int len = 0, cnt = -1;
    str += '.';
    for(int i{0}; i < str.length(); i++) {
        cnt++;
        if(isalpha(str[i])) {
            len++;
        }
        else if(ispunct(str[i]) || (str[i] == ' ' && isalpha(str[i-1]))) {
            if(len > res[1] && len != 0) {
                res[0] = cnt-len; // позиция слова
                res[1] = len; // длинна слова
            }
            len = 0;
        }
    }
    return res;
}

vector<int> minWord(string str) { // находим позицию и длинну самого короткого слова
    vector<int> res = {0, 100};
    int len = 0, cnt = -1;
    str += '.';
    for(int i{0}; i < str.length(); i++) {
        cnt++;
        if(isalpha(str[i])) {
            len++;
        }
        else if(ispunct(str[i]) || (str[i] == ' ' && isalpha(str[i-1]))) {
            if(len < res[1] && len != 0) {
                res[0] = cnt-len; // позиция слова
                res[1] = len; // длинна слова
            }
            len = 0;
        }
    }
    return res;
}

string swapWords(string str) { // меняем местами самое длинное и самое короткое слово
    if(str.back() != '.') str += '.';
    string copys = str;
    vector<int> maxw = maxWord(str);
    vector<int> minw = minWord(str);
    if(maxw[0] < minw[0]) {
        str.replace(minw[0], minw[1], copys.substr(maxw[0], maxw[1]));
        str.replace(maxw[0], maxw[1], copys.substr(minw[0], minw[1]));
    }
    else {
        str.replace(maxw[0], maxw[1], copys.substr(minw[0], minw[1]));
        str.replace(minw[0], minw[1], copys.substr(maxw[0], maxw[1]));
    }
    return str;
}

int main() {

    string str;
    cout << "Enter string: ";
    getline(cin, str);

    cout << "Result: " << swapWords(str) << endl;

    system("pause");
    return 0;

}
