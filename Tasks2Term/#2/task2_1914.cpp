#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Date {
    int d, m, y;
};

// перегружаем поток вывода для структуры даты
ostream& operator <<(ostream& os, const Date &date) {
    if(date.d < 10 && date.m < 10) return os << '0' << date.d << '.' << '0' << date.m << '.' << date.y;
    else if(date.d < 10) return os << '0' << date.d << '.' << date.m << '.' << date.y;
    else if(date.m < 10) return os << date.d << '.' << '0' << date.m << '.' << date.y;
    return os << date.d << '.' << date.m << '.' << date.y;
}

struct Employee {
    Date birth;
    string surname, post;
    int salary, exp;
};

// переводим строку в набор данных
Date toDate(string str) {
    Date newDate;
    str += '.';
    for(int i = 0; i < 3; i++) {
        string buf = str.substr(0, str.find_first_of("./"));
        if(i == 0) newDate.d = stoi(buf);
        else if(i == 1) newDate.m = stoi(buf);
        else if(i == 2) newDate.y = stoi(buf);
        str.erase(str.begin(), str.begin() + str.find_first_of("./") + 1);
    }
    return newDate;
}

// считываем данные из файла и создаём вектор
vector<Employee> createEmployees(string file) {
    vector<Employee> employees;
    string line;

    ifstream in;
    in.open(file);
    if(in.is_open()) {

        while(getline(in, line)) {
            Employee empl;
            line += ' ';
            for(int i = 0; i < 5; i++) {
                string buf = line.substr(0, line.find(' '));
                if(i == 0) empl.surname = buf;
                else if(i == 1) empl.post = buf;
                else if(i == 2) empl.birth = toDate(buf);
                else if(i == 3) empl.exp = stoi(buf);
                else if(i == 4) empl.salary = stoi(buf);
                line.erase(line.begin(), line.begin() + line.find(' ') + 1);
            }
            employees.push_back(empl);
        }

    }
    in.close();

    return employees;
}

// записываем данные в файл
void write(vector<Employee> v) {
    ofstream out;
    out.open("sorted.txt");
    if(out.is_open()) {
        for(auto empl: v) {
            out << empl.surname << ' ' << empl.post << ' ' << empl.birth << ' ' << empl.exp << ' ' << empl.salary << endl;
        }
    }
    out.close();
}

// быстрая сортировка по зарплате
void quickSort(vector<Employee> &v, int l, int r) {
    int pivot = v[(l + r) / 2].salary;
    int i = l, j = r;
    while(i < j) {
        if(v[i].salary > pivot) {
            swap(v[i].salary, v[j].salary);
            j--;
        }
        else if(v[j].salary < pivot) {
            swap(v[i], v[j]);
            i++;
        }
        else {
            i++;
            j--;
        }
    }
    if(j > l) quickSort(v, 0, j);
    if(i < r) quickSort(v, i, r);
}

// сортировка расчёсткой по году рождения и стажу работы
void combSort(vector<Employee> &v) {
    int gap = v.size();
    bool swapped = true;
    while(gap != 1 || swapped) {
        gap = gap / 1.347;
        if(gap < 1) gap = 1;
        swapped = false;
        for(int i = 0; i < v.size() - gap; i++) {
            if(v[i].birth.y > v[i + gap].birth.y ||
            (v[i].birth.y == v[i + gap].birth.y && v[i].exp > v[i].exp)) {
                swap(v[i], v[i + gap]);
                swapped = true; 
            }
        }
    }
}

// сортировка выбором по зарплате, году рождения и стажу работы
void selectionSort(vector<Employee> &v) {
    int minI, len = v.size();
    for(int i = 0; i < len - 1; i++) {
        minI = i;
        for(int j = i + 1; j < len; j++) {
            if(v[minI].salary > v[j].salary ||
            (v[minI].salary == v[j].salary && v[minI].birth.y > v[j].birth.y) || 
            (v[minI].salary == v[j].salary && v[minI].birth.y == v[j].birth.y && v[minI].exp > v[j].exp)) minI = j;
        }
        swap(v[i], v[minI]);
    }
}

int main() {

    int k = 3;
    char chose;
    vector<Employee> empls = createEmployees("data.txt");

    do {
        cout << "Make your chose (1 - counting sort, 2 - comb sort, 3 - selection sort): ";
        cin >> chose;
        switch(chose) {
            case '1':
                quickSort(empls, 0, empls.size() - 1);
                write(empls);
                cout << "Quick sort is complite!" << endl;
                k--;
                break;
            case '2':
                combSort(empls);
                write(empls);
                cout << "Comb sort is complite!" << endl;
                k--;
                break;
            case '3':
                selectionSort(empls);
                write(empls);
                cout << "Selection sort is complite!" << endl;
                k--;
                break;
            default:
                cout << "Incorrect input, try again" << endl;
                break;
        }
    } while(k);

    system("pause");
    return 0;

}