#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// метод деления по зарплате
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

    Employee(string _sur, string _p, Date _b, int _e, int _s) :
    surname(_sur), post(_p), birth(_b), exp(_e), salary(_s) {}
};

ostream& operator <<(ostream& os, const Employee &emp) {
    return os << emp.surname << " " << emp.post << " "
    << emp.birth << " " << emp.exp << " " << emp.salary;
}

// двусвязный список >>>
struct Node {
    Employee inf;
    Node* next;
    Node* prev;

    Node(Employee _inf) : inf(_inf), next(nullptr), prev(nullptr) {}
};

struct list {
    Node* head;
    Node* tail;

    list() : head(nullptr), tail(nullptr) {}

    bool is_empty() {
        return head == nullptr;
    }

    void push_back(Employee _inf) {
        Node* p = new Node(_inf);
        if (is_empty()) {
            head = tail = p;
        } else {
            p->prev = tail;
            tail->next = p;
            tail = p;
        }
    }

    bool remove(Node* node) {
        if (node == nullptr) return false;
        
        if (node == head && node == tail) {
            head = tail = nullptr;
        }
        else if (node == head) {
            head = head->next;
            if (head) head->prev = nullptr;
        }
        else if (node == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        }
        else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        
        delete node;
        return true;
    }

    void print() {
        Node* cur = head;
        while (cur) {
            cout << cur->inf << endl;
            cur = cur->next;
        }
    }
};
// <<< двусвязный список

int m;
vector<list> htable;

// вставка нового элемента а хэш-таблицу
void insert(string surname, string post, string date, int exp, int salary) {
    htable[exp % m].push_back(Employee(surname, post, toDate(date), exp, salary));
}

// считываем данные из файла и создаём хэш-таблицу
void readData(const string& fileName, int m) {
    htable.resize(m);
    ifstream file(fileName);

    string line;

    while (getline(file, line)) {
        istringstream iss(line);

        string surname, post, date;
        int salary, exp; 
        iss >> surname >> post >> date >> exp >> salary;

        insert(surname, post, date, exp, salary);
    }
}

// поиск всех элементов по стажу работы
vector<Node*> find(int x) {
    vector<Node*> vec;
    Node* r = htable[x % m].head;
    while (r) {
        if (r->inf.exp == x)
            vec.push_back(r);
        r = r->next;
    }
    return vec;
}

// удаление всех элементов по стажу работы
void del(int x) {
    Node* r = htable[x % m].head;
    while (r) {
        Node* next = r->next;
        if (r->inf.exp == x)
            htable[x % m].remove(r);
        r = next;
    }
}

int main() {

    cout << "Enter size of hash-table: ";
    cin >> m;
    readData("data.txt", m);

    char k;
    do {
        int exp, salary;
        string surname, post, date;

        cout << "1 - Print hash-tabel \n2 - Add new employee"
        << "\n3 - Find employees \n4 - Remove employees \n0 - End \n";

        cin >> k;
        switch (k) {
        case '0':
            return 0;
        case '1':
            cout << "Hash-table: " << endl;
            for (auto lst: htable) {
                if (!lst.is_empty()) {
                    lst.print();
                }
            }
            cout << endl;
            break;
        case '2':
            cout << "Enter surname: "; cin >> surname;
            cout << "Enter post: "; cin >> post;
            cout << "Enter date (dd.mm.yyyy): "; cin >> date;
            cout << "Enter exp: "; cin >> exp;
            cout << "Enter salary: "; cin >> salary;
            cout << "New employee has been added!" << endl;
            insert(surname, post, date, exp, salary);
            break;
        case '3':
            cout << "Enter exp of finding employees: "; cin >> exp;
            cout << "They are here: " << endl;
            for (auto emp: find(exp)) {
                cout << emp->inf << endl;
            }
            break;
        case '4':
            cout << "Enter exp of removing employees: "; cin >> exp;
            cout << "Removal successful!" << endl;
            del(exp);
            break;
        default:
            cout << "Invalid input, try again!";
            break;
        }
    } while (k != 0);

    return 0;

}