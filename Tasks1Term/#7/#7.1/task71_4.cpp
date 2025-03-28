#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Дан файл, содержащий расписание движения поездов в виде:
// Маршрут - время отправления - время в пути.
// Вывести в новый файл данные о поездах, которые
// прибываеют на конечную станцию в промежутке от 12 до 15 часов.

struct Time {
    int h, m;
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

    string line;
    vector<string> res;
    ifstream in("trains.txt"); // открываем файл для чтения

    if(in.is_open()) { // выполняем пока файл открыт

        while(getline(in, line)) { // считываем сроки пока есть
            string times, timed;
            timed = line.substr(line.rfind(" - ")+3, 5);
            times = line.substr(line.rfind(" - ")-5, 5);

            if(correct(times) && correct(timed)) {
                if(timeFin(strToTime(times), strToTime(timed)).h > 12 && timeFin(strToTime(times), strToTime(timed)).h < 15) {
                    res.push_back(line);
                }
            }

        }

    }

    in.close(); // закрываем файл

    ofstream out;
    out.open("result.txt"); // создаём новый файл и открываем его

    if(out.is_open()) {

        out << "Рейсы, которые прибудут на станцию с 12.00 по 15.00:\n";
        for(string train: res) { 
            out << train << '\n';
        }

    }

    out.close(); // закрываем файл

    return 0;

}