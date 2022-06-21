#include <iostream>

using namespace std;

class ABank;

class IBank;

class CBank {
public:
    explicit CBank(int _balance) : thisBalance(_balance) {
        balance += _balance;
    }

    int getBalance() const { return thisBalance; };

    friend int total(const CBank &c, const ABank &b, const IBank &i);

private:
    int thisBalance;
    static int balance;
};

class ABank {
public:
    explicit ABank(int _balance) : thisBalance(_balance) {
        balance += _balance;
    }

    int getBalance() const { return thisBalance; };

    friend int total(const CBank &c, const ABank &b, const IBank &i);

private:
    int thisBalance;
    static int balance;
};

class IBank {
public:
    explicit IBank(int _balance) : thisBalance(_balance) {
        balance += _balance;
    }

    int getBalance() const { return thisBalance; };

    friend int total(const CBank &c, const ABank &b, const IBank &i);

private:
    int thisBalance;
    static int balance;
};

int CBank::balance = 0;
int ABank::balance = 0;
int IBank::balance = 0;

int total(const CBank &c, const ABank &b, const IBank &i) {
    return CBank::balance + ABank::balance + IBank::balance;
}

int main() {
    int balance;
    cout << "Please set balance for CBank c1,c2 , ABank a1,a2,a3 and IBank i1." << endl;

    cin >> balance;
    CBank c1(balance);
    cin >> balance;
    CBank c2(balance);

    cin >> balance;
    ABank a1(balance);
    cin >> balance;
    ABank a2(balance);
    cin >> balance;
    ABank a3(balance);

    cin >> balance;
    IBank i1(balance);

    cout << "Your total balance is " << total(c1, a1, i1) << endl;
    cout << "Your balance at CBank c1 is " << c1.getBalance() << endl;
    cout << "Your balance at CBank c2 is " << c2.getBalance() << endl;
    cout << "Your balance at ABank a1 is " << a1.getBalance() << endl;
    cout << "Your balance at ABank a2 is " << a2.getBalance() << endl;
    cout << "Your balance at ABank a3 is " << a3.getBalance() << endl;
    cout << "Your balance at IBank i1 is " << i1.getBalance() << endl;

    return 0;
}