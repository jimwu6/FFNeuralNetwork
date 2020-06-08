#include "SetWrapper.h"
#include "Activations.h"
#include <string>
#include <time.h>

class Dataset {

public:

    // fields
    SetWrapper *training_set;
    SetWrapper *valid_set;
    SetWrapper *test_set;

    int input_count;
    int output_count; // this should be the number of classes that this dataset has (e.g for banknotes it would be 2)

    // methods
    
    // constructor and initializing
    Dataset(int in_cnt, int out_cnt);
    void createSet(std::string file_name, std::string set_name);
    
    // NN methods
    Matrix feedForward(Matrix inputs, Matrix weights, Matrix bias, Matrix &net);
    Matrix initializeWeights(double max_weight, int w, int h);
    void evalError(Matrix inputs, Matrix weight, Matrix outputs, Matrix mat_class, Matrix bias, double &error, double &c_error, int samples);
    void evalErrorSet(SetWrapper set_w, Matrix weights, double &error, double &c_error);
    void backprop(Matrix inputs, Matrix &weights, Matrix outputs, double alpha, Matrix bias);
    Matrix train(std::vector<std::vector<double>> &errors);
    // destructor
    ~Dataset();
};