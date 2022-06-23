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
              p(_x2, _y2, _z2), h(getPoint2().getZ() - p.getZ()) {}

    Box(const Box &b) : Rectangle(b.getPoint1(), b.getPoint2()),
                        p(b.getP()), h(b.getH()) {}

    double surface() const;

    double volume() const;

    bool isBox() const { return h != 0; };

    Point getP() const { return p; };

    double getH() const { return abs(h); };

private:
    Point p;
    double h;
};

double Box::volume() const {
    return Rectangle::area() * abs(h);
}

double Box::surface() const {
    return 2 * (Rectangle::area() +
                abs(h) * abs(getPoint1().getX() - getPoint2().getX()) +
                abs(h) * abs(getPoint1().getY() - getPoint2().getY()));
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
    Box b1(x1, y1, z1, x2, y2, z2);
    cout << "Box b1:" << endl;
    if (b1.isRectangle() && b1.isBox()) {
        cout << "Bottom Area = " << b1.area() << endl;
        cout << "Surface area = " << b1.surface() << endl;
        cout << "Volume = " << b1.volume() << endl;
    } else {
        cout << "b1 is not a valid box." << endl;
    }
    Box b2(b1);
    cout << "create b2 using copy constructor." << endl;
    cout << "Box b2:" << endl;
    if (b2.isRectangle() && b2.isBox()) {
        cout << "Bottom Area = " << b2.area() << endl;
        cout << "Surface area = " << b2.surface() << endl;
        cout << "Volume = " << b2.volume() << endl;
    } else {
        cout << "b2 is not a valid box." << endl;
    }

    return 0;
}