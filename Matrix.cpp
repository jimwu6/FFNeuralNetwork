// Matrix Class
// Jim Wu

#include "Matrix.h"

using namespace std;

Matrix::Matrix() {
}

Matrix::Matrix(const vector<vector<double>> &newarr) {
    array = newarr;
}
 
// identity matrix
Matrix Matrix::eye(int n) const {
    vector<vector<double>> arr(n, vector<double> (n, 0));
    for (int i = 0; i < n; i++) {
        arr[i][i] = 1;
    }
    Matrix m (arr);
    return m;
}

// transpose
Matrix Matrix::transpose() const {
    vector<vector<double>> newarr (array[0].size(), vector<double> (array.size(), 0));
    for (int i = 0; i < array[0].size(); i++) {
        for (int j = 0; j < array.size(); j++) {
            newarr[i][j] = array[j][i];
        }
    }

    Matrix out (newarr);
    return out;
}

// add matrix
Matrix Matrix::add(const Matrix &newmat) const {
    if (array.size() != newmat.array.size() || array[0].size() != newmat.array[0].size()) {
        cout << "Dims are wrong: in Matrix A+B, A = " << array.size() << "x" << array[0].size();
        cout << ", B = " << newmat.array.size() << "x" << newmat.array[0].size() << "\n";
    }

    vector<vector<double>> newarr = array;
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array[0].size(); j++) {
            newarr[i][j] += newmat.array[i][j];
        }
    }
    Matrix out(newarr);
    return out;
}

// add constant value
Matrix Matrix::add(double x) const {
    vector<vector<double>> newarr = array;
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array[0].size(); j++) {
            newarr[i][j] += x;
        }
    }

    Matrix out (newarr);
    return out;
}

Matrix Matrix::scalarMultiply(double k) const {
    vector<vector<double>> newarr = array;
    for (int i = 0; i < newarr.size(); i++) {
        for (int j = 0; j < newarr[0].size(); j++) {
            newarr[i][j] *= k;
        }
    }

    Matrix out (newarr);
    return out;
}

Matrix Matrix::multiply(const Matrix &mat) const {
    
    int ar1 = array.size();
    int ar2 = array[0].size();
    int mat1 = mat.array.size();
    int mat2 = mat.array[0].size();
    if (ar2 != mat1) {
        cout << "Mismatch dim of matrix multiply\n";
    }

    vector<vector<double>> newarr(ar1, vector<double> (mat2, 0));
    for (int i = 0; i < ar1; i++) {
        for (int j = 0; j < mat2; j++) {
            double sum = 0;
            for (int k = 0; k < ar2; k++) {
                sum += array[i][k] * mat.array[k][j];
            }
            newarr[i][j] = sum;
        }
    }

    Matrix out(newarr);
    return out;
}

// elementwise multiplication
Matrix Matrix::Hadamard(const Matrix &mat) const {

    vector<vector<double>> newarr = array;
    if (array.size() != mat.array.size() || array[0].size() != mat.array[0].size()) {
        cout << "Mismatch dim of Hadamard";
    }

    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array[0].size(); j++) {
            newarr[i][j] *= mat.array[i][j];
        }
    }
    
    Matrix out (newarr);
    return out;

}

// only implemented for product of row and column vector
Matrix Matrix::Kronecker(const Matrix &mat) const {
    if (array.size() != 1 || mat.array[0].size() != 1) {
        cout << "Mismatch dim of Kronecker\n";
    }

    vector<vector<double>> newarr(mat.array.size(), vector<double> (array[0].size(), 0));

    for (int i = 0; i < array[0].size(); i++) {
        for (int j = 0; j < mat.array.size(); j++) {
            newarr[i][j] = array[0][i] * mat.array[j][0];
        }
    }

    Matrix out(newarr);
    return out;
}

Matrix Matrix::horizontalConcat(const Matrix &mat) const {
    int ar1 = array.size(), ar2 = array[0].size();
    int mat1 = mat.array.size(), mat2 = mat.array[0].size();

    if (ar1 != mat1) {
        cout << "Mismatch size of horizontal concat\n";
    }

    vector<vector<double>> newarr(ar1, vector<double> (ar2+mat2, 0));

    for (int i = 0; i < ar1; i++) {
        for (int j = 0; j < ar2; j++) {
            newarr[i][j] = array[i][j];
        }
        for (int j = ar2; j < ar2+mat2; j++) {
            newarr[i][j] = mat.array[i][j-ar2];
        }
    }

    Matrix out(newarr);
    return out;
}

Matrix Matrix::verticalConcat(const Matrix &mat) const {
    int ar1 = array.size(), ar2 = array[0].size();
    int mat1 = mat.array.size(), mat2 = mat.array[0].size();

    if (ar2 != mat2) {
        cout << "Mismatch size of vertical concat\n";
    }
    vector<vector<double>> newarr(ar1+mat1, vector<double> (ar2, 0));
    
    for (int i = 0; i < ar1; i++) {
        for (int j = 0; j < ar2; j++) {
            newarr[i][j] = array[i][j];
        }
    }
    for (int i = ar1; i < ar1+mat1; i++) {
        for (int j = 0; j < mat2; j++) {
            newarr[i][j] = mat.array[i-ar1][j];
        }
    }

    Matrix out(newarr);
    return out;
}

double Matrix::difference(const Matrix &mat) const {
    if (array.size() != mat.array.size() || array[0].size() != mat.array[0].size()) {
        cout << "Mismatched dims in difference\n";
    }
    double d = 0;
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array[0].size(); j++) {
            if (array[i][j] != mat.array[i][j]) d += 1;
        }
    }
    return d;
}

double Matrix::sumElements(const int times) const {
    double sum = 0;
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array[0].size(); j++) {
            double s = 1;
            for (int k = 0; k < times; k++) {
                s *= array[i][j];
            }
            sum += s;
        }
    }
    return sum;
}

// converts :
// 1 0 0              0
// 0 1 0              1
// 0 0 1  --->        2
// 1 0 0              0
// 0 0 1              2
Matrix Matrix::toClass() const {
    vector<vector<double>> newarr(array.size(), vector<double> (1, 0));
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array[0].size(); j++) {
            if (array[i][j] == 1) {
                // change to j+1 if 1-indexed
                newarr[i][0] = j;
                break;
            }
        }
    }

    Matrix out(newarr);
    return out;
}

// converts :
// 0              1 0 0
// 1              0 1 0
// 2      --->    0 0 1
// 0              1 0 0
// 2              0 0 1
Matrix Matrix::toOutput(const int numClasses) const {
    vector<vector<double>> newarr(array.size(), vector<double> (numClasses, 0));
    for (int i = 0; i < array.size(); i++) {
        // change to array[i][0]-1 if 1-indexed
        newarr[i][array[i][0]] = 1;
    }

    Matrix out(newarr);
    return out;
}

void Matrix::print() const {
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array[0].size(); j++) {
            cout << array[i][j] << " "; 
        }
        cout << "\n";
    }
}

vector<int> Matrix::size() const {
    vector<int> sz(2, 0);

    sz[0] = array.size();
    if (!sz[0]) return sz;
    sz[1] = array[0].size();

    return sz;
}

void Matrix::toFile(string s) const {
    ofstream output;
    output.open("./out_data/" + s);
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array[0].size(); j++) {
            output << array[i][j] << "\t";
        }
        output << "\n";
    }
    output.close();
}

Matrix::~Matrix() {
}