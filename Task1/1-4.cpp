#include <iostream>
#include <cstdlib>

using namespace std;

class Point;

class Rectangle {
public:
    Rectangle(Point &_p1, Point &_p2) : p1(_p1), p2(_p2) {}

    bool isRectangle() const;

    double area() const;

private:
    Point &p1, &p2;
};

class Point {
public:
    Point(double _x, double _y) : x(_x), y(_y) {}

    double getX() const { return this->x; }

    double getY() const { return this->y; }

private:
    double x, y;
};

bool Rectangle::isRectangle() const {
    return p1.getX() != p2.getX() && p1.getY() != p2.getY();
}

double Rectangle::area() const {
    return abs((p1.getX() - p2.getX())*(p1.getY() - p2.getY()));
}

int main() {
    double x1, y1, x2, y2;
    cout << "Please input two points: x1,y1,x2,y2." << endl;
    cin >> x1 >> y1 >> x2 >> y2;
    Rectangle rect(*new Point(x1, y1), *new Point(x2, y2));
    if (rect.isRectangle()) {
        cout << "This is a rectangle." << endl;
        cout << "Area = " << rect.area() << endl;
    } else {
        cout << "This is not a rectangle." << endl;
    }
    return 0;
}