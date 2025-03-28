#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// считываем данные из файла
vector<vector<int>> read(string file) {
    vector<vector<int>> v;
    string line;
    ifstream in;
    in.open(file);
    if(in.is_open()) {
        while(getline(in, line)) {
            line += ' ';
            vector<int> a;
            while(line.find(' ') != -1) {
                string buf = line.substr(0, line.find(' '));
                a.push_back(stoi(buf));
                line.erase(line.begin(), line.begin() + line.find(' ') + 1);
            }
            v.push_back(a);
        }
    }
    in.close();
    return v;
}

// записываем данные в файл
void write(vector<vector<int>> v) {
    ofstream out;
    out.open("sorted.txt");
    if(out.is_open()) {
        for(auto row: v) {
            for(auto elem: row) {
                out << elem << ' ';
            }
            out << endl;
        }
    }
    out.close();
}

// сортировка подсчётом по строкам
void countingSort(vector<vector<int>> &v, int row) { 
    int minVal = v[row][0];
    int maxVal = v[row][0];
    for(auto elem: v[row]) {
        if(elem > maxVal) maxVal = elem;
        if(elem < minVal) minVal = elem;
    }

    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);
    for(auto elem: v[row]) count[elem - minVal]++;
    
    int index = 0;
    for(int i = 0; i < count.size(); i++) {
        while(count[i] > 0) {
            v[row][index++] = i + minVal;
            count[i]--;
        }
    }
}

// нечёт - по убыванию, чёт - по возрастанию гномьей сортировкой
void gnomeSort(vector<vector<int>> &v, int row) {
    bool isOdd = (row + 1) % 2 == 0;
    int i = 0, j = 1;
    while(j < v[row].size()) {
        if(isOdd) {
            if(v[row][i] > v[row][j]) {
                swap(v[row][i], v[row][j]);
                i = 0;
                j = 1;
            }
            else {
                i++;
                j++;
            }
        }

        else {
            if(v[row][i] < v[row][j]) {
                swap(v[row][i], v[row][j]);
                i = 0;
                j = 1;
            }
            else {
                i++;
                j++;
            } 
        }
    }
}

// сортировка пузырьком для диагоналей параллельных побочной
void bubbleSort(vector<int> &diag) {
    for(int i = 1; i < diag.size(); i++) {
        for(int j = 0; j < diag.size() - i; j++) {
            if(diag[j] > diag[j+1]) swap(diag[j], diag[j+1]);
        }
    }
}

void sorted(vector<vector<int>> &v, char sort) {
    if(sort == '1') for(int row = 0; row < v.size(); row++) countingSort(v, row);
    else if(sort == '2') for(int row = 0; row < v.size(); row++) gnomeSort(v, row);
    else if(sort == '3') {
        for(int i = 1; i < v.size()*2 - 2; i++) {
            vector<int> diag;
            for(int j = 0; j < v.size(); j++) {
                if(i - j < v.size() && i - j >= 0) diag.push_back(v[j][i - j]);
            }
            bubbleSort(diag);
            int k = 0;
            for(int j = 0; j < v.size(); j++) {
                if(i - j < v.size() && i - j >= 0) {
                    v[j][i - j] = diag[k];
                    k++;
                }
            }
        }
    }
}

int main() {

    int k = 3;
    char chose;
    vector<vector<int>> arr;

    do {
        cout << "Make your chose (1 - countin sort, 2 - gnome sort, 3 - bubble sort): ";
        cin >> chose;
        switch(chose) {
            case '1':
                arr = read("data2.txt");
                sorted(arr, chose);
                write(arr);
                cout << "Counting sort complite!" << endl;;
                k--;
                break;
            case '2':
                arr = read("data2.txt");
                sorted(arr, chose);
                write(arr);
                cout << "Gnome sort complite!" << endl;;
                k--;
                break;
            case '3':
                arr = read("data2.txt");
                sorted(arr, chose);
                write(arr);
                cout << "Bubble sort complite!" << endl;;
                k--;
                break;
            default:
                cout << "Wrong input! Try again!" << endl;
                break;
        }
    } while(k != 0);

    system("pause");
    return 0;

}