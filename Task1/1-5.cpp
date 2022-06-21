#include <iostream>

using namespace std;

class Complex {
public:
    Complex(double _a, double _b) : a(_a), b(_b) {}

    Complex operator+(Complex z) const { return {a + z.a, b + z.b}; };

    Complex operator-(Complex z) const { return {a - z.a, b - z.b}; };

    Complex operator*(Complex z) const { return {a * z.a - b * z.b, b * z.a + a * z.b}; };

    void showValue() const;

    friend Complex add(Complex z1, Complex z2) { return {z1.a + z2.a, z1.b + z2.b}; };

private:
    double a, b;
};

void Complex::showValue() const {
    if (a == 0 && b == 0) cout << 0;
    else if (a == 0) cout << b << "i";
    else if (b == 0) cout << a;
    else if (b == 1) cout << a << " + i";
    else if (b < 0) cout << a << " - " << -b << "i";
    else cout << a << " + " << b << "i";
}

int main() {
    int a, b;
    cout << "Please input z1." << endl;
    cin >> a >> b;
    Complex z1(a, b);
    cout << "Please input z2." << endl;
    cin >> a >> b;
    Complex z2(a, b);
    Complex z3 = z1 + z2;
    Complex z4 = add(z1, z2);
    Complex z5 = z1 - z2;
    Complex z6 = z1 * z2;
    cout << "z1 = ";
    z1.showValue();
    cout << endl;
    cout << "z2 = ";
    z2.showValue();
    cout << endl;
    cout << "z1 + z2 = ";
    z3.showValue();
    cout << endl;
    cout << "add(z1, z2) = ";
    z4.showValue();
    cout << endl;
    cout << "z1 - z2 = ";
    z5.showValue();
    cout << endl;
    cout << "z1 * z2 = ";
    z6.showValue();
    cout << endl;
    return 0;
}