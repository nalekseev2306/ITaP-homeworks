#include <iostream>
#include <string>

using namespace std;

// Создать структуру Train, содержащую данные о номере поезда,
// времени отправления, времени в пути. Определить для каждого поезда
// время прибытия на конечную станцию. Необходима проверка на
// корректность ввода времени

struct Time {
    int h, m;

    void print() { // выводит время
        if(h < 10 || m < 10) {
            if(h >= 10 && m < 10) cout << h << ".0" << m; 
            else if(h < 10 && m >= 10) cout << '0' << h << '.' << m;
            else cout << '0' << h << ".0" << m; 
        }
        else cout << h << '.' << m;
    }

};

Time strToTime(string str) { // переводит строку во время
    Time time;
    time.h = stoi(str.substr(0, 2));
    time.m = stoi(str.substr(3, 2));
    return time;
}

bool correct(string str) { // проверяет корректность времени
    if (str.length() != 5) return false;
    for(int i{0}; i < str.length(); i++) {
        if (!ispunct(str[i])) {
            if (!isdigit(str[i])) return false;
        }
    }
    Time time = strToTime(str);
    if (time.h < 0 || time.h > 23) return false;
    if (time.m < 0 || time.m > 59) return false;
    return true;
}

struct Train {
    int number;
    Time timeStart, timeDur;
};

Train *create(int n) { // создаёт массив поездов
    Train *trains = new Train[n];
    string s1, s2;
    for(int i{0}; i < n; i++) {
        cout << "Enter " << i+1 << " Start time and Time duration as hh.mm: ";
        cin >> s1 >> s2;
        trains[i].number = i+1;
        if(correct(s1) && correct(s2)) {
            trains[i].timeStart = strToTime(s1);
            trains[i].timeDur = strToTime(s2);
        }  
        else {
            trains[i].timeStart = strToTime("00.00");
            trains[i].timeDur = strToTime("00.00");
        } 
    }
    return trains; 
}

Time timeFin(Time t1, Time t2) { // определят время прибытия
    Time newTime;
    if(t1.m + t2.m >= 60) {
        newTime.m = t1.m + t2.m - 60;
        if(t1.h + t2.h + 1 >= 24) newTime.h = t1.h + t2.h + 1 - 24;
        else newTime.h = t1.h + t2.h + 1;
    }
    else {
        newTime.m = t1.m + t2.m;
        if(t1.h + t2.h >= 24) newTime.h = t1.h + t2.h - 24;
        else newTime.h = t1.h + t2.h; 
    }
    return newTime;
}

int main() {

    int n;
    cout << "Enter number of trains: ";
    cin >> n;
    Train *trains = create(n);

    for(int i{0}; i < n; i++) {
        cout << "Arrival time of train number " << i+1 << ": ";
        timeFin(trains[i].timeStart, trains[i].timeDur).print();
        cout << endl;
    }

    system("pause");
    return 0;

}