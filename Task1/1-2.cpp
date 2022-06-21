#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

int func(int n) {
    try {
        if (n > 1000) throw invalid_argument("n should be less than 1000!");
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
        return 0;
    }
    int sum = 0;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            sum += (i + n / i);
        }
    }
    return sum;
}

int main() {
    int n;
    cin >> n;
    int result = func(n);
    cout << "sum=" << result << endl;
    return 0;
}
