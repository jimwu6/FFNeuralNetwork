#include "Matrix.h"

class SetWrapper {

public:

    Matrix inputs; // features
    Matrix outputs; // one-hot encoding
    Matrix classes; // column vector, with each element corresponding to the class number (e.g. 0 or 1)
    Matrix bias; // column vector with each element being 1
    int count;

    // methods
    SetWrapper();
    void read(std::ifstream &file, int inputCount, int outputCount);
    ~SetWrapper();

};