#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<int> strToVector() {
    vector<int> arr;
    string str;
    cout << "Enter numbers: ";
    getline(cin, str);
    str += ' ';
    while(str != "") {
        string buf = str.substr(0, str.find_first_of(' '));
        arr.push_back(stoi(buf));
        str.erase(str.begin(), str.begin() + str.find_first_of(' ') + 1);
    }
    return arr;
}

void printVector(vector<int> arr) {
    for(int num: arr) {
        cout << num << ' ';
    }
    cout << endl;
}

// возвращает количество цифр в числе 
int digitCount(int num) {
    int count = 0;
    while(abs(num) > 0) {
        num /= 10;
        count++;
    }
    return count;
}

// возвращает цифру с указаной позиции
int getDigit(int num, int pos) {
    int div = pow(10, pos - 1);
    if(pos == 1) return abs(num) % 10;
    else if(pos > 1) return (abs(num) / div) % 10;
    return 0;
}

// возвращает наибольшее количество цифр из массива чисел
int maxDigits(vector<int> arr) {
    int max = INT_MIN;
    for(int num: arr) if(digitCount(num) > max) max = digitCount(num);
    return max;
}

// поразрядная сортировка от старшего к младшему
void radixSort(vector<int>& arr, int pos) {
    if(pos <= 0 || arr.size() <= 1) return ;

    vector<vector<int>> posBuckets(10);
    vector<vector<int>> negBuckets(10);

    for(int num: arr)
        num >= 0 ?
        posBuckets[getDigit(num, pos)].push_back(num):
        negBuckets[getDigit(num, pos)].push_back(num);

    for(auto& bucket: posBuckets)
        if(!bucket.empty()) radixSort(bucket, pos - 1);
    
    for(auto& bucket: negBuckets)
        if(!bucket.empty()) radixSort(bucket, pos - 1);

    int i = 0;
    for(int j = 9; j >= 0; j--) {
        for(int num: negBuckets[j]) {
            arr[i++] = num;
        }
    }
    for(auto bucket: posBuckets) {
        for(int num: bucket) {
            arr[i++] = num;
        }
    }

}

int main() {

    vector<int> arr = strToVector();
    radixSort(arr, maxDigits(arr));

    cout << "Sorted vector: ";
    printVector(arr);

    system("pause");
    return 0;

}