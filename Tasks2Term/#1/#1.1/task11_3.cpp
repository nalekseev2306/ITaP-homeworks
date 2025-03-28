#include <iostream>
#include <list>
#include <numeric>
#include <functional>

using namespace std;

list<double> makeList(int n) { // создаём список элементов
    double a;
    list<double> lst;
    cout << "Enter elements: ";
    for(int i{0}; i < n; i++) {
        cin >> a;
        lst.push_back(a);
    }
    return lst;
}

int main() {

    int n;
    cout << "Enter length of list: ";
    cin >> n;
    list<double> lst = makeList(n);

    // функция поиска среднего значения в списке
    function<double(list<double>)> meanVal = [](list<double> lst){return accumulate(lst.begin(), lst.end(), 0.0) / size(lst);};
    // функция подсчёта дисперсии
    function<double(list<double>)> dispersion =

    [meanVal](list<double> lst){return accumulate(lst.begin(), lst.end(), 0.0,
    [lst, meanVal](double sum, double x){return sum + (x - meanVal(lst)) * (x - meanVal(lst));}) / (lst.size() - 1);};

    cout << "Dispersion = " << dispersion(lst) << endl;

    system("pause");
    return 0;
    
}