#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Array {
public:
    Array() : capacity(0), length(0), baseAddress(nullptr) {}

    explicit Array(int _capacity) : capacity(_capacity), length(0), baseAddress(new T[_capacity]) {}

    Array(const Array<T> &array);

    ~Array();

    Array &operator=(const Array &src);

    bool operator==(const Array &src) const;

    T &operator[](int index) const;

    T *begin() const { return baseAddress; };

    T *end() const { return baseAddress + length; };

    bool empty() const { return length == 0; };

    int getLength() const { return length; };

    int getCapacity() const { return capacity; };

    void resize(int newCapacity);

    T *find(const T &e) const;

    T *find(const T &e, bool (*comp)(const T &a, const T &b)) const;

    void reverse(T *start, T *end);

    T *insert(T *it, const T &e);

    void push_back(const T &e);

    T *erase(T *pos);

    void pop_back();

private:
    int capacity;
    int length;
    T *baseAddress;
};

template<typename T>
Array<T>::~Array() {
    delete[] baseAddress;
    baseAddress = nullptr;
    capacity = 0;
    length = 0;
}

template<typename T>
Array<T>::Array(const Array<T> &array):capacity(array.capacity), length(array.length) {
    baseAddress = new T[array.capacity];
    for (int i = 0; i < array.length; i++) {
        baseAddress[i] = array.baseAddress[i];
    }
}

template<typename T>
Array<T> &Array<T>::operator=(const Array<T> &src) {
    if (this == &src) return *this;
    if (this->baseAddress != nullptr) {
        delete[] baseAddress;
    }
    baseAddress = new T[src.capacity];
    capacity = src.capacity;
    length = src.length;
    for (int i = 0; i < length; ++i) {
        baseAddress[i] = src.baseAddress[i];
    }
    return *this;
}

template<typename T>
T &Array<T>::operator[](int index) const {
    return baseAddress[index];
}

template<typename T>
bool Array<T>::operator==(const Array<T> &src) const {
    if (capacity != src.capacity || length != src.length) return false;
    for (int i = 0; i < length; ++i) {
        if (baseAddress[i] != src.baseAddress[i]) return false;
    }
    return true;
}


template<typename T>
void Array<T>::resize(int newCapacity) {
    if (capacity < newCapacity) {
        T *newBaseAddress = new T[newCapacity];
        for (int i = 0; i < length; ++i) {
            newBaseAddress[i] = baseAddress[i];
        }
        delete[] baseAddress;
        capacity = newCapacity;
        baseAddress = newBaseAddress;
    } else {
        if (length > newCapacity) {
            capacity = length = newCapacity;
        } else if (capacity > newCapacity) {
            capacity = newCapacity;
        }
    }
}

template<typename T>
T *Array<T>::find(const T &e) const {
    for (T *it = this->begin(); it != this->end(); ++it) {
        if (*it == e) {
            return it;
        }
    }
    return baseAddress;
}

template<typename T>
T *Array<T>::find(const T &e, bool (*comp)(const T &a, const T &b)) const {
    for (T *it = this->begin(); it != this->end(); ++it) {
        if (comp(*it, e)) {
            return it;
        }
    }
    return baseAddress;
}

template<typename T>
void Array<T>::reverse(T *start, T *end) {
    for (int i = 0; i < (end - start) / 2; i++) {
        T t = baseAddress[i];
        baseAddress[i] = baseAddress[end - start - i - 1];
        baseAddress[end - start - i - 1] = t;
    }
}

template<typename T>
T *Array<T>::insert(T *it, const T &e) {
    int index = it - baseAddress;
    try {
        if (index >= length) throw out_of_range("Exceed length limit.");
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    if (capacity == 0) {
        capacity = 1;
        baseAddress = new T[capacity];
    } else if (length + 1 > capacity) {
        capacity *= 2;
        T *newBaseAddress = new T[capacity];
        for (int i = 0; i < length; ++i) {
            newBaseAddress[i] = baseAddress[i];
        }
        delete[] baseAddress;
        baseAddress = newBaseAddress;
    }
    for (int i = length - 1; i >= index; --i) {
        baseAddress[i + 1] = baseAddress[i];
    }
    baseAddress[index] = e;
    length++;
    return it;
}

template<typename T>
void Array<T>::push_back(const T &e) {
    if (capacity == 0) {
        capacity = 1;
        baseAddress = new T[capacity];
    } else if (length + 1 > capacity) {
        capacity *= 2;
        T *newBaseAddress = new T[capacity];
        for (int i = 0; i < length; ++i) {
            newBaseAddress[i] = baseAddress[i];
        }
        delete[] baseAddress;
        baseAddress = newBaseAddress;
    }
    baseAddress[length] = e;
    length++;
}

template<typename T>
T *Array<T>::erase(T *pos) {
    try {
        if (pos >= end()) throw invalid_argument("pos should be less than end.");
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
        return pos;
    }
    for (int i = pos - baseAddress; i < length; ++i) {
        baseAddress[i] = baseAddress[i + 1];
    }
    length--;
    return pos;
}

template<typename T>
void Array<T>::pop_back() {
    length--;
}

int main() {
    cout << "----Create Array----" << endl;
    Array<int> arr1;
    cout << "Create arr1 with default constructor." << endl;
    Array<int> arr2(10);
    cout << "Create arr2 with capacity 10." << endl;
    cout << "arr1 init capacity: " << arr1.getCapacity() << endl;
    cout << "arr2 init capacity: " << arr2.getCapacity() << endl;

    cout << "----Push Elements----" << endl;
    cout << "Push elements into arr1:" << endl;
    arr1.push_back(1);
    cout << "Pushed 1 into arr1." << endl;
    arr1.push_back(2);
    cout << "Pushed 2 into arr1." << endl;
    arr1.push_back(3);
    cout << "Pushed 3 into arr1." << endl;
    arr1.insert(arr1.begin() + 2, 4);
    cout << "Inserted 4 into arr1 at position begin() + 2." << endl;

    cout << "arr1 now capacity: " << arr1.getCapacity() << endl;
    arr1.push_back(5);
    cout << "Pushed 5 into arr1.(Capacity doubled)" << endl;
    cout << "arr1 now capacity: " << arr1.getCapacity() << endl;

    cout << "----Array Traverse----" << endl;
    cout << "range-based for loop traverse of arr1:" << endl;
    for (int &i: arr1) {
        cout << i << endl;
    }
    cout << "iterator-based for loop traverse of arr1:" << endl;
    for (auto i = arr1.begin(); i != arr1.end(); ++i) {
        cout << *i << endl;
    }

    cout << "----Search Elements----" << endl;
    cout << "Find 4 in arr1." << endl;
    auto index = arr1.find(4) - arr1.begin();
    cout << "Found 5 in arr1 at index " << index << " ." << endl;
    cout << "Find 3 in arr1." << endl;
    index = arr1.find(3) - arr1.begin();
    cout << "Found 3 in arr1 at index " << index << " ." << endl;
    cout << "Find 3 in arr1 using custom function." << endl;
    index = arr1.find(3, [](const int &a, const int &b) -> bool { return a == b; }) - arr1.begin();
    cout << "Found 3 in arr1 at index " << index << " ." << endl;


    cout << "----Create Array From Existing Array----" << endl;
    arr2 = arr1;
    cout << "assign arr2 from arr1." << endl;
    cout << "arr2:" << endl;
    for (int &i: arr2) {
        cout << i << endl;
    }
    Array<int> arr3(arr1);
    cout << "create arr3 from arr1 using copy constructor." << endl;
    cout << "arr3:" << endl;
    for (int &i: arr3) {
        cout << i << endl;
    }

    cout << "----Reverse Array----" << endl;
    cout << "arr1 before reverse:" << endl;
    for (int &i: arr1) {
        cout << i << endl;
    }
    cout << "reverse arr1 from begin() to end() using member function." << endl;
    arr1.reverse(arr1.begin(), arr1.end());
    for (int &i: arr1) {
        cout << i << endl;
    }
    cout << "reverse arr2 from begin() to end() using reverse() in <algorithm> ." << endl;
    reverse(arr2.begin(), arr2.end());
    for (int &i: arr2) {
        cout << i << endl;
    }
    cout << "verify if arr2==arr1 after reverse in two different ways." << endl;
    cout << "if arr1==arr2? result: " << (arr1 == arr2 ? "true" : "false") << endl;

    cout << "----Sort Array----" << endl;
    cout << "sort arr1 from begin() to end() using sort() in <algorithm>." << endl;
    sort(arr1.begin(), arr1.end(), less<int>());
    cout << "arr1 after sort:" << endl;
    for (int &i: arr1) {
        cout << i << endl;
    }

    cout << "----Resize Array----" << endl;
    arr1.resize(3);
    cout << "resize arr1 to size 3" << endl;
    cout << "arr1 after resize:" << endl;
    for (int &i: arr1) {
        cout << i << endl;
    }

    cout << "----Pop Elements from Array----" << endl;
    cout << "arr2:" << endl;
    for (int &i: arr2) {
        cout << i << endl;
    }
    arr2.pop_back();
    cout << "pop back element from arr2." << endl;
    arr2.pop_back();
    cout << "pop back element from arr2." << endl;
    cout << "arr2:" << endl;
    for (int &i: arr2) {
        cout << i << endl;
    }
    cout << "----Erase Array----" << endl;
    arr2.erase(arr2.begin() + 1);
    cout << "erase the second element from arr2." << endl;
    arr2.erase(arr2.begin() + 1);
    cout << "erase the second element from arr2." << endl;
    cout << "arr2:" << endl;
    for (int &i: arr2) {
        cout << i << endl;
    }
    arr2.erase(arr2.begin());
    cout << "erase the first element from arr2." << endl;
    cout << "arr2 length: " << arr2.getLength() << endl;
    cout << "if arr2 is empty? result: " << (arr2.empty() ? "true" : "false") << endl;
    return 0;
}