#include "SetWrapper.h"
#include <string>

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
    Matrix feedForward(Matrix inputs, Matrix bias, Matrix weights, Matrix &net);
    Matrix initializeWeights(double max_weight, int w, int h);

    // destructor
    ~Dataset();
};