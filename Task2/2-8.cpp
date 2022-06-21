#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <iomanip>

using namespace std;

class Student {
public:
    Student() : id(0),
                programming(0),
                network(0),
                database(0),
                sum(0) {}

    Student(int _id, string _name, int _programming, int _network, int _database) : id(_id),
                                                                                    name(move(_name)),
                                                                                    programming(_programming),
                                                                                    network(_network),
                                                                                    database(_database),
                                                                                    sum(_programming + _network +
                                                                                        _database) {}

    int getID() const { return id; };

    string getName() const { return name; };

    int getProgrammingScore() const { return programming; };

    int getNetworkScore() const { return network; };

    int getDatabaseScore() const { return database; };

    int getSumScore() const { return sum; }


private:
    int id;
    string name;
    int programming;
    int network;
    int database;
    int sum;
};

int getDigitCount(int num) {
    int count = 0;
    while (num) {
        num /= 10;
        count++;
    }
    return count;
}

void printStudent(int T, const Student s[], int maxIDLength, unsigned long int maxNameLength) {
    cout << setw(maxIDLength) << left << "ID" << "  "
         << setw((int) (max(maxNameLength / 3 * 2, (unsigned long int) 4))) << left << "Name" << "  "
         << "Programming Network Database Sum"
         << endl;
    for (int i = 0; i < T; ++i) {
        cout << setw(maxIDLength) << left << s[i].getID() << "  "
             << setw((int) (maxNameLength + 1 - (maxNameLength - s[i].getName().length()) / 3)) << s[i].getName()
             << "  "
             << setw(11) << left << s[i].getProgrammingScore() << " "
             << setw(7) << left << s[i].getNetworkScore() << " "
             << setw(8) << left << s[i].getDatabaseScore() << " "
             << s[i].getSumScore() << endl;
    }
    cout << endl;
}

void printStudent(const vector<Student> &stu, int maxIDLength, unsigned long int maxNameLength) {
    cout << setw(maxIDLength) << left << "ID" << "  "
         << setw((int) (max(maxNameLength / 3 * 2, (unsigned long int) 4))) << left << "Name" << "  "
         << "Programming Network Database Sum"
         << endl;
    for (const Student &s: stu) {
        cout << setw(maxIDLength) << left << s.getID() << "  "
             << setw((int) (maxNameLength + 1 - (maxNameLength - s.getName().length()) / 3)) << s.getName() << "  "
             << setw(11) << left << s.getProgrammingScore() << " "
             << setw(7) << left << s.getNetworkScore() << " "
             << setw(8) << left << s.getDatabaseScore() << " "
             << s.getSumScore() << endl;
    }
    cout << endl;
}

int main() {
    int T, maxIDLength = 0;
    unsigned long int maxNameLength = 0;
    cout << "Please input student quantity." << endl;
    cin >> T;
    Student s[T];
    cout << "Please input each student's score." << endl;
    cout << "ID Name Programming Network Database" << endl;
    for (int i = 0; i < T; i++) {
        int id, programming, network, database;
        string name;
        cin >> id >> name >> programming >> network >> database;
        maxIDLength = maxIDLength > getDigitCount(id) ? maxIDLength : getDigitCount(id);
        maxNameLength = maxNameLength > name.length() ? maxNameLength : name.length();
        s[i] = Student(id, name, programming, network, database);
    }

    sort(s, s + T, [](const Student &a, const Student &b) { return a.getSumScore() > b.getSumScore(); });
    cout << "Sort by sum score." << endl;
    printStudent(T, s, maxIDLength, maxNameLength);

    sort(s, s + T,
         [](const Student &a, const Student &b) { return a.getProgrammingScore() > b.getProgrammingScore(); });
    cout << "Sort by programming score." << endl;
    printStudent(T, s, maxIDLength, maxNameLength);

    sort(s, s + T, [](const Student &a, const Student &b) { return a.getNetworkScore() > b.getNetworkScore(); });
    cout << "Sort by network score." << endl;
    printStudent(T, s, maxIDLength, maxNameLength);

    sort(s, s + T, [](const Student &a, const Student &b) { return a.getDatabaseScore() > b.getDatabaseScore(); });
    cout << "Sort by database score." << endl;
    printStudent(T, s, maxIDLength, maxNameLength);

    sort(s, s + T, [](const Student &a, const Student &b) { return a.getSumScore() > b.getSumScore(); });
    vector<Student> satisfied;
    for (const Student &stu: s) {
        if (stu.getProgrammingScore() >= 85 && stu.getNetworkScore() >= 85 && stu.getDatabaseScore() >= 85) {
            satisfied.push_back(stu);
            maxIDLength = maxIDLength > getDigitCount(stu.getID()) ? maxIDLength : getDigitCount(stu.getID());
            maxNameLength = maxNameLength > stu.getName().length() ? maxNameLength : stu.getName().length();
        }
    }
    cout << "All scores are above 85, Sort by sum score." << endl;
    printStudent(satisfied, maxIDLength, maxNameLength);

    return 0;
}