#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <time.h>

using namespace std;

// отобразить состояние ответа
void printAnswer(vector<char> answer) {
    for(int i{0}; i < size(answer); i++) {
        cout << answer[i] << ' ';
    }
}

void drawViselica(int attemptsLeft) {
    vector<string> viselica = {
        "          \n |\n |\n |\n |\n |\n_|_",
        "  ________\n |\n |\n |\n |\n |\n_|_",
        "  ________\n |        |\n |\n |\n |\n |\n_|_",
        "  ________\n |        |\n |        O\n |\n |\n |\n_|_",
        "  ________\n |        |\n |        O\n |        |\n |\n |\n_|_",
        "  ________\n |        |\n |        O\n |       /|\n |\n |\n_|_",
        "  ________\n |        |\n |        O\n |       /|\\\n |\n |\n_|_",
        "  ________\n |        |\n |        O\n |       /|\\\n |       / \n |\n_|_",
        "  ________\n |        |\n |        O\n |       /|\\\n |       / \\\n |\n_|_",
        "  ________\n |        |\n |        O\n |       /|\\\n |       / \\\n |    GAME OVER\n_|_"};
    if(size(viselica) != attemptsLeft) cout << viselica[size(viselica) - attemptsLeft - 1];
}

// обновить записи в терминал
void rewriteTerminal(vector<char> answer, int attempts, set<char> alph, bool flag1, bool flag2, bool flag3, string gameMode) {
    system("cls");
    cout << "Alph: "; for(auto it = alph.begin(); it != alph.end(); it++) if(*it != '\0') cout << *it << ' '; cout << endl;
    cout << "Letters: " << size(answer) << "    ";
    printAnswer(answer);
    if(gameMode == "1") cout << "   " << "Attemts: " << attempts << endl;
    else if(gameMode == "2") {cout << endl; drawViselica(attempts); cout << endl;}
    if(flag1) cout << "Letter has already been used" << endl;
    if(flag2) cout << "Correct" << endl;
    if(flag3) cout << "Incorrect" << endl;
}

// ввод буквы / слова
char makeGuess(string word, vector<char> answer, int attempts, set<char> alph, bool flag1, bool flag2, bool flag3, string gameMode) { 
    string str;
    char guess;
    cout << "Enter letter or word: ";
    getline(cin, str);
    if(size(str) == 1 && isalpha(str[0])) {
        guess = str[0];
        return guess;
    }
    if(size(str) >= 8 && size(str) < 16) {
        if(str == word) return '+';
        else return '-';
    }
    rewriteTerminal(answer, attempts, alph, flag1, flag2, flag3, gameMode);
    cout << "Wrong input! Try again" << endl;
    return makeGuess(word, answer, attempts, alph, flag1 = false, flag2 = false, flag3 = false, gameMode);
}

// проверка условий победы / поражения
bool winLose(int attempts, int lettersLeft, char guess) { 
    if(guess == '+') {
        cout << "You WIN!" << endl;
        return false;
    }
    else if(guess == '-') {
        cout << "You LOSE!" << endl;
        return false;
    }
    else if(lettersLeft == 0) {
        cout << "You WIN!" << endl;
        return false;
    }
    else if(attempts == 0) {
        cout << "You LOSE!" << endl;
        return false;
    }
    return true;
}
// контейнер для определения буквы и её позиции
multimap<char, int> wordToLetters(string word) { 
    multimap<char, int> letters;
    for(int i{0}; i < size(word); i++) {
        letters.insert(make_pair(word[i], i));
    }
    return letters;
}

// получаем позиции корректных букв
vector<int> getIters(char guess, multimap<char, int> letters) { 
    vector<int> iters;
    auto range = letters.equal_range(guess);
    for(auto it = range.first; it != range.second; it++) {
        iters.push_back(it->second);
    }
    return iters;
}

// обновляем состояние алфавита
set<char> refreshAlph(set<char> alph, char guess) { 
    for(auto it = alph.begin(); it != alph.end(); it++) {
        if(*it == guess) {
            it = alph.erase(it);
            break;
        }
    }
    return alph;
}

int main() {

    srand(time(0));

    vector<string> words = {"federation", "adventure", "basketball", "chocolate", "friendship",
                            "imagination", "relationship", "satisfaction", "transportation", "understanding"};
    vector<char> answer;
    string word = words[rand() % size(words)];
    int lettersLeft = size(word);
    set<char> alph;
    for(char let: "qwertyuiopasdfghjklzxcvbnm") alph.insert(let);
    for(int i{0}; i < size(word); i++) answer.push_back('_');

    bool game = true;
    int attempts = 10;
    string gameMode;
    bool flag1 = false, flag2 = false, flag3 = false;

    cout << "Chose game mode (1 - countdown, 2 - hangman): ";
    getline(cin, gameMode);
    rewriteTerminal(answer, attempts, alph, flag1, flag2, flag3, gameMode);

    while(game) {

        flag1 = false, flag2 = false, flag3 = false;
        char guess = makeGuess(word, answer, attempts, alph, flag1, flag2, flag3, gameMode);
        game = winLose(attempts, lettersLeft, guess);

        if(!game) break;

        if(alph.find(guess) != alph.end()) {

            alph = refreshAlph(alph, guess);

            if(word.find(guess) != -1) {
                auto iters = getIters(guess, wordToLetters(word));
                for(auto i: iters) {
                    answer[i] = guess;
                    lettersLeft--;
                    flag2 = true;
                }
            }
            else {
                attempts--;
                flag3 = true;
            }
        }
        else flag1 = true;

        rewriteTerminal(answer, attempts, alph, flag1, flag2, flag3, gameMode);

        game = winLose(attempts, lettersLeft, guess);

    }

    system("pause");
    return 0;

}