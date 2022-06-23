#include <iostream>
#include <cstring>

using namespace std;

class Matrix {
public:
    Matrix(int r, int c) : row(r), col(c) {
        baseAddress = new int[row * col];
    }

    Matrix(int r, int c, int *base) : row(r), col(c), baseAddress(base) {}

    Matrix(const Matrix &m) : row(m.row), col(m.col) {
        baseAddress = new int[m.col * m.row];
        memcpy(baseAddress, m.baseAddress, m.col * m.row);
    }

    ~Matrix() {
        delete[] baseAddress;
        baseAddress = nullptr;
        row = 0;
        col = 0;
    }

    void inputMatrix();

    void outputMatrix();

    bool isIdentity() const;

    bool isDiagonal() const;

    Matrix transpose();

    Matrix operator+(const Matrix &m);

    Matrix operator-(const Matrix &m);

    Matrix operator*(const Matrix &m);

    Matrix operator*(int lambda);

    bool operator==(const Matrix &m) const;

private:
    int row;
    int col;
    int *baseAddress;
};

void Matrix::inputMatrix() {
    cout << "Please input a " << row << " x " << col << " matrix." << endl;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> baseAddress[i * col + j];
        }
    }
}

void Matrix::outputMatrix() {
    cout << "This is a " << row << " x " << col << " matrix." << endl;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << baseAddress[i * col + j] << " ";
        }
        cout << endl;
    }
}

bool Matrix::isIdentity() const {
    Matrix e(col, col);
    for (int i = 0; i < col; ++i) {
        e.baseAddress[i * col + i] = 1;
    }
    return *this == e;
}

bool Matrix::isDiagonal() const {
    if (col != row) return false;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i != j && baseAddress[i * col + j] != 0) return false;
        }
    }
    return true;
}

Matrix Matrix::transpose() {
    int *newBaseAddress = new int[row * col];
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            newBaseAddress[i * row + j] = baseAddress[j * col + i];
        }
    }
    return {col, row, newBaseAddress};
}

Matrix Matrix::operator+(const Matrix &m) {
    try {
        if (m.row != row || m.col != col) throw invalid_argument("different types of matrix.");
    }
    catch (exception &e) {
        cout << "Error: " << e.what() << endl;
        return {0, 0};
    }
    int *newBaseAddress = new int[row * col];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            newBaseAddress[i * col + j] = baseAddress[i * col + j] + m.baseAddress[i * col + j];
        }
    }
    return {row, col, newBaseAddress};
}

Matrix Matrix::operator-(const Matrix &m) {
    try {
        if (m.row != row || m.col != col) throw invalid_argument("different types of matrix.");
    }
    catch (exception &e) {
        cout << "Error: " << e.what() << endl;
        return {0, 0};
    }
    int *newBaseAddress = new int[row * col];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            newBaseAddress[i * col + j] = baseAddress[i * col + j] - m.baseAddress[i * col + j];
        }
    }
    return {row, col, newBaseAddress};
}

Matrix Matrix::operator*(const Matrix &m) {
    try {
        if (m.row != col || m.col != row) throw invalid_argument("mxn ≠ nxm. Cannot multiple.");
    }
    catch (exception &e) {
        cout << "Error: " << e.what() << endl;
        return {0, 0};
    }
    int _row, _col;
    _row = _col = row;
    int *newBaseAddress = new int[_row * _col];
    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _col; ++j) {
            for (int k = 0; k < col; ++k) {
                newBaseAddress[i * _col + j] += baseAddress[i * col + k] * m.baseAddress[k * m.col + j];
            }
        }
    }
    return {_row, _col, newBaseAddress};
}

Matrix Matrix::operator*(int lambda) {
    int *newBaseAddress = new int[row * col];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            newBaseAddress[i * col + j] = baseAddress[i * col + j] * lambda;
        }
    }
    return {row, col, newBaseAddress};
}

bool Matrix::operator==(const Matrix &m) const {
    if (col != m.col || row != m.row) return false;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (baseAddress[i * col + j] != m.baseAddress[i * col + j]) return false;
        }
    }
    return true;
}

int main() {
    cout << "Please input the number of row and column of matrix A." << endl;
    int row, col;
    cin >> row >> col;
    Matrix a(row, col);
    cout << "Please input the number of row and column of matrix B." << endl;
    cin >> row >> col;
    Matrix b(row, col);
    cout << "Please input matrix A." << endl;
    a.inputMatrix();
    cout << "Please input matrix B." << endl;
    b.inputMatrix();
    cout << "A + B:" << endl;
    (a + b).outputMatrix();
    cout << "A - B:" << endl;
    (a - b).outputMatrix();
    cout << "A * B:" << endl;
    (a * b).outputMatrix();
    cout << "A * AT:" << endl;
    (a * a.transpose()).outputMatrix();
    cout << "A * 5:" << endl;
    (a * 5).outputMatrix();
    cout << "if A is a identity matrix? " << (a.isIdentity() ? "true" : "false") << endl;
    cout << "if A is a diagonal matrix? " << (a.isDiagonal() ? "true" : "false") << endl;
    return 0;
}