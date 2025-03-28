#include <iostream>
#include <cmath>

using namespace std;

// условие задачи

struct point { // структура точки
    double x, y;
};

point* create(int n) { // создаём массив из точек
    point *arr = new point[n];
    for(int i{0}; i < n; i++) {
        cout << "Input " << i << " point coordinates (x, y):" << endl;
        cin >> arr[i].x >> arr[i].y;
    }
    return arr;
}

double length(point a, point b) { // расстояние между двумя точками
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

point maxSum(point *points, int n) { // точка с наибольшей суммой расстояния до других точек
    double maxs = 0, sum = 0;
    point ans;
    for(int i{0}; i < n; i++) {
        for(int j{0}; j < n; j++) {
            sum += length(points[i], points[j]);
        }
        if(sum > maxs) {
            maxs = sum;
            ans = points[i];
        }
        sum = 0;
    }
    return ans;
}

int main() {

    int n;
    cout << "Enter count of points: ";
    cin >> n;
    point *points = create(n);
    point ans = maxSum(points, n);

    cout << "Answer: (" << ans.x << ", " << ans.y << ")" << endl;

    system("pause");
    return 0;

}