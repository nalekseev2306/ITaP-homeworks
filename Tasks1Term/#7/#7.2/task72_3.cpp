#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct fraction {
    int integer = 0, chisl, znam;
};

fraction strToDrob(string str) { // считываем дробь из строки
    fraction drob;
    drob.chisl = stoi(str.substr(0, str.find('/')));
    drob.znam = stoi(str.substr(str.find('/') + 1, str.length() - str.find('/') - 1));
    return drob;
}

void print(fraction drob) { // вывести дробь
    if(drob.integer == 0 && drob.chisl != 0) cout << drob.chisl << "/" << drob.znam;
    else if(drob.integer != 0 && drob.chisl != 0) cout << drob.integer << "+" << drob.chisl << "/" << drob.znam;
    else cout << drob.integer;
}

fraction sum(fraction a, fraction b) { // сумма
    fraction newDrob;
    if(a.znam == b.znam) {
        newDrob.chisl = a.chisl + b.chisl;
        newDrob.znam = a.znam;
    }
    else {
        newDrob.znam = a.znam * b.znam;
        newDrob.chisl = a.chisl * b.znam + b.chisl * a.znam;
    } 
    return newDrob;
}

fraction diff(fraction a, fraction b) { // разность
    fraction newDrob;
    if(a.znam == b.znam) {
        newDrob.chisl = a.chisl - b.chisl;
        newDrob.znam = a.znam;
    }
    else {
        newDrob.znam = a.znam * b.znam;
        newDrob.chisl = a.chisl * b.znam - b.chisl * a.znam;
    } 
    return newDrob;
}

fraction mult(fraction a, fraction b) { // произведение
    fraction newDrob;
    newDrob.chisl = a.chisl * b.chisl;
    newDrob.znam = a.znam * b.znam;
    return newDrob;
}

fraction div(fraction a, fraction b) { // деление
    fraction newDrob;
    newDrob.chisl = a.chisl * b.znam;
    newDrob.znam = a.znam * b.chisl;
    return newDrob;
}

fraction reduce(fraction drob) { // сокращение дроби
    fraction newDrob;
    while(drob.chisl % 2 == 0 && drob.znam % 2 == 0) {
        drob.chisl /= 2;
        drob.znam /= 2;
    }
    if(drob.chisl != 1 && drob.znam != 1) {
        for(int i{3}; i*i <= min(drob.chisl, drob.znam)*min(drob.chisl, drob.znam); i+=2) {
            if(drob.chisl % i == 0 && drob.znam % i == 0) {
                drob.chisl /= i;
                drob.znam /= i;
            }
        }
    }
    if(drob.znam == 1) {
        newDrob.integer = drob.chisl;
        newDrob.chisl = 0;
        newDrob.znam = 1;
    }
    else {
        newDrob.chisl = drob.chisl;
        newDrob.znam = drob.znam;
    }
    return newDrob;
}

double drobToDecimal(fraction drob) { // перевод в десятичную дробь
    if(drob.integer == 0) return drob.chisl * 1. / drob.znam;
    else return drob.integer + (drob.chisl * 1. / drob.znam);
}

fraction toRightDrob(fraction drob) { // перевод в правильную дробь
    if(drob.chisl == drob.znam) {
        drob.integer = 1;
        drob.chisl = 0;
    }
    else if(drob.chisl > drob.znam) {
        drob.integer = drob.chisl / drob.znam;
        drob.chisl -= drob.integer * drob.znam;
    }
    return drob;
}

bool correct(string str) { // проверяет корректно ли введены данные
    if(str.find('/') != str.rfind('/')) return false;
    for(int i{0}; i < str.find('/'); i++) {
        if(!isdigit(str[i])) return false;
    }
    for(int i = str.find('/')+1; i < str.length(); i++) {
        if(!isdigit(str[i])) return false;
    }
    if(str[0] != '0' && str[str.find('/')+1] != '0') return true;
    else return false;
}

int main() {

    string str1, str2;
    
    cout << "Input first drob: ";
    cin >> str1;
    cout << "Input second drob: ";
    cin >> str2;
    if(correct(str1) && correct(str2)) {
        fraction drob1, drob2;
        drob1 = strToDrob(str1);
        drob2 = strToDrob(str2);

        cout << "Summa: ";
        print(sum(drob1, drob2));
        cout << endl << "Difference: ";
        print(diff(drob1, drob2));
        cout << endl << "Multiply: ";
        print(mult(drob1, drob2));
        cout << endl << "Division: ";
        print(div(drob1, drob2));

        cout << endl << "Reduce: ";
        print(reduce(drob1));
        cout << endl << "Decimal: ";
        cout << drobToDecimal(drob2);
        cout << endl << "Right drob: ";
        print(toRightDrob(drob1));
    } 
    else {
        cout << "Input ERROR!";
    }

    cout << endl;
    system("pause");
    return 0;

}