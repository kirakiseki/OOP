#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>

using namespace std;

class Point {
public:
    Point(double _x, double _y) : x(_x), y(_y) {}

    double getX() const { return x; }

    double getY() const { return y; }

private:
    double x, y;
};

class Circle : public Point {
public:
    Circle(double _x, double _y, float &r) : Point(_x, _y), radius(&r) {}

    float getRadius() { return *radius; }

private:
    float *radius;
};

double distance(Circle a, Circle b) {
    return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
}

enum relation {
    intersect,   //相交
    disjoint,    //外离
    contain,     //内含
    inscribe,    //内切
    circumscribe //外切
};

relation judge(Circle c1, Circle c2, double(*distanceFunc)(Circle a, Circle b)) {
    double d = distanceFunc(c1, c2);
    if (c1.getRadius() + c2.getRadius() > d && d > abs(c1.getRadius() - c2.getRadius())) return intersect;
    else if (c1.getRadius() + c2.getRadius() < d) return disjoint;
    else if (d == 0 || d < abs(c1.getRadius() - c2.getRadius())) return contain;
    else if (d == abs(c1.getRadius() - c2.getRadius())) return inscribe;
    else return circumscribe;
}

int main() {
    map<relation, string> mp;
    mp.insert(pair<relation, string>(intersect, "intersect"));
    mp.insert(pair<relation, string>(disjoint, "disjoint"));
    mp.insert(pair<relation, string>(contain, "contain"));
    mp.insert(pair<relation, string>(inscribe, "inscribe"));
    mp.insert(pair<relation, string>(circumscribe, "circumscribe"));

    double x, y;
    float r1, r2;
    cout << "Please two circles: x1 y1 r1, x2 y2 r2." << endl;
    cin >> x >> y >> r1;
    Circle c1(x, y, r1);
    cin >> x >> y >> r2;
    Circle c2(x, y, r2);
    cout << "C1: center = (" << c1.getX() << "," << c1.getY() << "), r = " << c1.getRadius() << endl;
    cout << "C2: center = (" << c2.getX() << "," << c2.getY() << "), r = " << c2.getRadius() << endl;
    cout << "Relation between c1 and c2: " << mp.find(judge(c1, c2, distance))->second << endl;
    return 0;
}