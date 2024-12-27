#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

struct Point {
    int x;
    int y;
};

bool withinDistance(const Point& point, int distance) {
    int dx = point.x;
    int dy = point.y;
    return sqrt(dx * dx + dy * dy) <= distance;
}

void filterPointsByDistance(const vector<Point>& points, int distance) {
    set<Point> filteredPoints;

    for (const Point& point : points) {
        if (withinDistance(point, distance)) {
            filteredPoints.insert(point);
        }
    }

    for (const Point& point : filteredPoints) {
        cout << "(" << point.x << ", " << point.y << ") ";
    }
}

int32_t main() {
    vector<Point> points = {
        {1, 1}, {-2, 3}, {4, -1}, {0, 0}, {3, 4}, {-5, -5}
    };
    int distance = 3;

    cout << "Points within distance " << distance << " from the origin: ";
    filterPointsByDistance(points, distance);
    cout << endl;

    return 0;
}
