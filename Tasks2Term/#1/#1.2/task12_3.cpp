#include <iostream>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

string toLower(string s) { // перевод в нижний регистр
    for(int i = 0; i < s.length(); i++) s[i] = tolower(s[i]);
    return s;
}

set<string> toWords(string s) { // разбиение предложения на слова
    s += ' ';
    set<string> words;
    while(s.find(' ') != -1) {
        words.insert(s.substr(0, s.find(' ')));
        s.erase(s.begin(), s.begin() + s.find(' ') + 1);
    }
    return words;
}

int main() {

    string str;
    set<string> pov, voskl, vopr, res;
    cout << "Enter text: ";
    getline(cin, str);
    str = toLower(str + ' ');

    // разбиваем текст на предложения и классифицируем их
    while(str.find_first_of(".!?") != -1) {
        set<string> tmp = toWords(str.substr(0, str.find_first_of(".!?")));
        if(str[str.find_first_of(".!?")] == '.') pov.insert(tmp.begin(), tmp.end());
        if(str[str.find_first_of(".!?")] == '!') voskl.insert(tmp.begin(), tmp.end());
        if(str[str.find_first_of(".!?")] == '?') vopr.insert(tmp.begin(), tmp.end());
        str.erase(str.begin(), str.begin() + str.find_first_of(".!?") + 2);
    }

    // объединение множеств
    set_intersection(pov.begin(), pov.end(), vopr.begin(), vopr.end(), inserter(res, res.begin()));

    cout << "Answer: ";
    for(auto word: res) {
        cout << word << ' ';
    }
    cout << endl;

    system("pause");
    return 0;

}