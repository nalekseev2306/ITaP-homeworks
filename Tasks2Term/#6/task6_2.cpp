#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// основная - линейное хэширование, вспомогательная - метод деления по году
using namespace std;

struct Date {
    int d, m, y;
};

// переводим строку в дату
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

// перегружаем поток вывода для структуры даты
ostream& operator <<(ostream& os, const Date &date) {
    if(date.d < 10 && date.m < 10)
        return os << '0' << date.d << '.' << '0' << date.m << '.' << date.y;
    else if(date.d < 10)
        return os << '0' << date.d << '.' << date.m << '.' << date.y;
    else if(date.m < 10)
        return os << date.d << '.' << '0' << date.m << '.' << date.y;
    return os << date.d << '.' << date.m << '.' << date.y;
}

struct Employee {
    Date birth;
    string surname, post;
    int salary, exp;
    bool is_empty = true;

    Employee(string _sur, string _p, Date _b, int _e, int _s) :
    surname(_sur), post(_p), birth(_b), exp(_e), salary(_s), is_empty(false) {}

    Employee() : is_empty(true) {}
};

ostream& operator <<(ostream& os, const Employee &emp) {
    return os << emp.surname << " " << emp.post << " "
    << emp.birth << " " << emp.exp << " " << emp.salary;
}

int m, n;
vector<Employee> htable;

// вставка нового элемента а хэш-таблицу
void insert(string surname, string post, string date, int exp, int salary) {
    int j = 0;
    while (j < m) {
        if (htable[toDate(date).y % m + j].is_empty) {
            htable[toDate(date).y % m + j] = Employee(surname, post, toDate(date), exp, salary);
            break;
        }
        j++;
    }
}

// считываем данные из файла и создаём хэш-таблицу
void readData(const string& fileName) {
    ifstream file(fileName);

    string line;
    getline(file, line);
    istringstream iss(line);
    iss >> n;

    if (n > m) m = n;
    htable.resize(m, Employee());


    while (getline(file, line)) {
        istringstream iss(line);

        string surname, post, date;
        int salary, exp;
        iss >> surname >> post >> date >> exp >> salary;
        
        insert(surname, post, date, exp, salary);
    }
}

// поиск всех элементов по году рождения
vector<Employee> find(int year) {
    int j = 0;
    vector<Employee> vec;
    while (j < m) {
        if (htable[year % m + j].surname == "") break;
        else if (htable[year % m + j].birth.y == year)
            vec.push_back(htable[year % m + j]);
        j++;
    }
    return vec;
}

int main() {

    cout << "Enter size of hash-table: ";
    cin >> m;
    readData("data.txt");

    char k;
    do {
        int exp, salary, year;
        string surname, post, date;

        cout << "1 - Print hash-tabel \n2 - Add new employee"
        << "\n3 - Find employees \n0 - End \n";

        cin >> k;
        switch (k) {
        case '0':
            return 0;
        case '1':
            cout << "Hash-table: " << endl;
            for (Employee emp: htable) {
                static int i = 0;
                cout << i << " ";
                if (!emp.is_empty) cout << emp;
                cout << endl;
                i++;
            }
            cout << endl;
            break;
        case '2':
            if (m > n) {
                cout << "Enter surname: "; cin >> surname;
                cout << "Enter post: "; cin >> post;
                cout << "Enter date (dd.mm.yyyy): "; cin >> date;
                cout << "Enter exp: "; cin >> exp;
                cout << "Enter salary: "; cin >> salary;
                cout << "New employee has been added!" << endl;
                insert(surname, post, date, exp, salary);
                n++;
            }
            else cout << "Hash-table is overflowing!" << endl;
            break;
        case '3':
            cout << "Enter birth year of finding employees: "; cin >> year;
            cout << "They are here: " << endl;
            for (Employee emp: find(year))
                cout << emp << endl;
            break;
        default:
            cout << "Invalid input, try again!";
            break;
        }
    } while (true);

    return 0;

}