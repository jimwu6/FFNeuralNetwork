#include "Activations.h"

using namespace std;

// (tanh(x)+1) / 2
Matrix Hyperbolic(const Matrix &mat) {
    vector<vector<double>> newarr = mat.array;

    for (int i = 0; i < mat.array.size(); i++) {
        for (int j = 0; j < mat.array[0].size(); j++) {
            newarr[i][j] = (tanh(newarr[i][j]) + 1) / 2;
        }
    }
    Matrix out (newarr);
    return out;
};

// (1-tanh^2(x)) / 2
Matrix HyperbolicPrime(const Matrix &mat) {
    vector<vector<double>> newarr = mat.array;

    for (int i = 0; i < mat.array.size(); i++) {
        for (int j = 0; j < mat.array[0].size(); j++) {
            newarr[i][j] = (1 - tanh(newarr[i][j]) * tanh(newarr[i][j])) / 2;
        }
    }
    Matrix out (newarr);
    return out;
};

// 1 / (1+e^-x)
Matrix Logistic(const Matrix &mat) {
    vector<vector<double>> newarr = mat.array;

    for (int i = 0; i < mat.array.size(); i++) {
        for (int j = 0; j < mat.array[0].size(); j++) {
            newarr[i][j] = 1 / (1 + exp(-newarr[i][j]));
        }
    }
    Matrix out (newarr);
    return out;
};

// e^-x / (1+e^-x)^2
Matrix LogisticPrime(const Matrix &mat) {
    vector<vector<double>> newarr = mat.array;

    for (int i = 0; i < mat.array.size(); i++) {
        for (int j = 0; j < mat.array[0].size(); j++) {
            double expon = exp(newarr[i][j]);
            newarr[i][j] = (expon) / ((1 + expon) * (1 + expon));
        }
    }
    Matrix out (newarr);
    return out;
};