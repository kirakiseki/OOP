#include <iostream>
#include <cstdlib>

using namespace std;

class Point;

class Rectangle {
public:
    Rectangle(Point &_p1, Point &_p2) : p1(_p1), p2(_p2) {}

    bool isRectangle() const;

    double area() const;

    Point &getPoint1() const { return p1; }

    Point &getPoint2() const { return p2; }

private:
    Point &p1, &p2;
};

class Point {
public:
    Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    double getX() const { return this->x; }

    double getY() const { return this->y; }

    double getZ() const { return this->z; }

private:
    double x, y, z;
};

class Box : public Rectangle {
public:
    Box(double _x1, double _y1, double _z1, double _x2, double _y2, double _z2)
            : Rectangle(*new Point(_x1, _y1, _z1),
                        *new Point(_x2, _y2, _z1)),
              p(_x2, _y2, _z2), h(abs(getPoint1().getZ() - p.getZ())) {}

    double surface() const;

    double volume() const;

    bool isBox() const { return h > 0; };

private:
    Point p;
    double h;
};

double Box::volume() const {
    return Rectangle::area() * h;
}

double Box::surface() const {
    return 2 * (Rectangle::area() +
                h * abs(getPoint1().getX() - getPoint2().getX()) +
                h * abs(getPoint1().getY() - getPoint2().getY()));
}

bool Rectangle::isRectangle() const {
    return p1.getX() != p2.getX() && p1.getY() != p2.getY();
}

double Rectangle::area() const {
    return abs((p1.getX() - p2.getX()) * (p1.getY() - p2.getY()));
}

int main() {
    double x1, y1, x2, y2, z1, z2;
    cout << "Please input two points: x1,y1,z1,x2,y2,z2." << endl;
    cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
    Box b(x1, y1, z1, x2, y2, z2);
    if (b.isRectangle() && b.isBox()) {
        cout << "Bottom Area = " << b.area() << endl;
        cout << "Surface area = " << b.surface() << endl;
        cout << "Volume = " << b.volume() << endl;
    } else {
        cout << "This is not a valid box." << endl;
    }
    return 0;
}