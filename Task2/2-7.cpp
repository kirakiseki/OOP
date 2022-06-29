#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Product {
public:
    Product(int _quantity, double _price) : quantity(_quantity), price(_price) {
        sum += (income = quantity * price);
        count += quantity;
        avg = sum / count;
    }

    int getQuantity() const { return quantity; };

    double getPrice() const { return price; };

    double getIncome() const { return income; };

    static double getSum() { return sum; };

    static double getAvg() { return avg; };

private:
    int quantity;
    double price;
    double income;
    static double sum;
    static double avg;
    static int count;
};

double Product::sum = 0;
double Product::avg = 0;
int Product::count = 0;

int main() {
    int T;
    vector<pair<int, Product>> sold;
    cout << "Please input salesman quantity." << endl;
    cin >> T;
    while (T--) {
        int id, quantity;
        double price;
        cout << "Please input this salesman's id quantity and price." << endl;
        cin >> id >> quantity >> price;
        sold.emplace_back(make_pair(id, *new Product(quantity, price)));
    }
    cout << "This product's Sum: "
         << Product::getSum()
         << " at average price: "
         << Product::getAvg() << endl;
    for (pair<int, Product> s: sold) {
        cout << "Salesman #" << s.first << endl;
        cout << "Sold quantity: " << s.second.getQuantity()
             << " at average price: " << s.second.getPrice()
             << " and get income: " << s.second.getIncome() << endl;
    }
    return 0;
}