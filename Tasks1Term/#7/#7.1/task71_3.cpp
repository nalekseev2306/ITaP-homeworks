#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Дано предложение. Вывести слова, содержащие наибольшее количество различных букв.

vector<string> strToWords(string str) { // превращает строку в массив слов
    vector<string> words;
    str += '.';
    string buf = "";
    for(int i{0}; i < str.length(); i++) {
        if(!ispunct(str[i]) && str[i] != ' ') {
            buf += str[i];
        }
        else if(ispunct(str[i]) || (str[i] == ' ' && !ispunct(str[i-1]))) {
            words.push_back(buf);
            buf = "";
        }
    }
    return words;
}

int cntLet(string word) { // определяет количество разных букв в слове
    int cnt = 0;
    string alph = "qwertyuiopasdfghjklzxcvbnm";
    for(char let: word) {
        if(alph.find_first_of(let) != -1) {
            alph.replace(alph.find(let), 1, "");
            cnt++;
        }
    }
    return cnt;
}

void task3(string str) { // выводит слова с максимальным количеством разных букв
    int max = 0;
    for(string word: strToWords(str)) {
        if(cntLet(word) >= max) max = cntLet(word);
    }
    for(string word: strToWords(str)) {
        if(cntLet(word) == max) cout << word << " ";
    }
}

int main() {

    string str;
    cout << "Enter string: ";
    getline(cin, str);

    cout << "Result: ";
    task3(str);

    cout << endl;
    system("pause");
    return 0;

}