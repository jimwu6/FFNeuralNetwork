// Matrix Header File
// Jim Wu

#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>


class Matrix {

public:

    // field
    std::vector< std::vector<double> > array;

    // constructors
    Matrix();
    Matrix(const std::vector< std::vector<double> > &newarr);
    // Matrix(const std::vector<double> &newarr);

    // identity matrix
    Matrix eye(int n) const;

    // basic operations
    Matrix transpose() const;
    Matrix add(const Matrix &newmat) const;
    Matrix add(double x) const;

    // multiply
    Matrix scalarMultiply(double k) const;
    Matrix multiply(const Matrix &mat) const;
    Matrix Hadamard(const Matrix &mat) const;
    Matrix Kronecker(const Matrix &mat) const; // only works for product of row and column vector

    // concatenation
    Matrix horizontalConcat(const Matrix &mat) const;
    Matrix verticalConcat(const Matrix &mat) const;

    // misc
    double difference(const Matrix &mat) const;
    double sumElements(const int times) const; // times used for exponent (e.g times = 1 is normal, times = 2 is elementwise squared)
    Matrix row(const int ind) const;

    // class conversion
    Matrix toClass() const;
    Matrix toOutput(const int numClasses) const;

    // debugging
    void print() const;
    std::vector<int> size() const;

    // to file
    void toFile(std::string s) const;

    // destructors
    ~Matrix();
};
