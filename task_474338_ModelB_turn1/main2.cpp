struct Point {
    double x;
    double y;
};

void printPoint(const Point& p) {
    printf("(%.2lf, %.2lf)\n", p.x, p.y);
}

int main() {
    Point p1 = {1.0, 2.0};
    printPoint(p1);
    return 0;
}
