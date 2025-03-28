#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <map>

using namespace std;

// прочитаем строку из файла
string readLine(string fileName) {
    string line;
    ifstream in(fileName);
    getline(in, line); 
    in.close();
    return line + ' ';
}

// подсчитаем количество вхождений числа в строку
map<int, int, greater<int>> mapOfNumbers(string s) {
    map<int, int, greater<int>> numbers;
    while(s != "") {
        string buf = s.substr(0, s.find(' '));
        if(all_of(buf.begin(), buf.end(), ::isdigit)) {
            numbers[stoi(buf)]++;
        }
        s.erase(s.begin(), s.begin() + s.find(' ') + 1);
    }
    return numbers;
}

// поменяем ключи и значения местами
map<int, int, greater<int>> flipMap(map<int, int, greater<int>> mp) {
    map<int, int, greater<int>> newMap;
    for(auto [key, value]: mp) {
        newMap[value] = key;
    }
    return newMap;
}

int main() {

    int k;
    string line = readLine("data.txt");
    map<int, int, greater<int>>nums = flipMap(mapOfNumbers(line));
    
    cout << "Enter k: ";
    cin >> k;
    
    cout << "Answer: ";
    for(auto it = nums.begin(); it != nums.end() && k > 0; it++, k--) {
        cout << it->second << " - " << it->first << ", ";
    }
    cout << endl;

    system("pause");
    return 0;

}