#include "Dataset.h"
#include "Activations.h"
#include <string>
#include <time.h>

using namespace std;

Dataset::Dataset(int in_cnt, int out_cnt) {
    input_count = in_cnt;
    output_count = out_cnt;
    training_set = new SetWrapper();
    valid_set = new SetWrapper();
    test_set = new SetWrapper();
};

void Dataset::createSet(string file_name, string set_name) {
    ifstream file;
    file.open(file_name);

    if (!file.is_open()) {
        cout << "WARNING: " << file_name << " could not be opened!\n";
        return;
    }
    else {
        cout << file_name << "opened!\n";
    }

    if (set_name == "train") {
        training_set->read(file, input_count, output_count);
    }
    else if (set_name == "valid") {
        valid_set->read(file, input_count, output_count);
    }
    else if (set_name == "test") {
        test_set->read(file, input_count, output_count);
    }

    file.close();
}

Matrix Dataset::feedForward(Matrix inputs, Matrix bias, Matrix weights, Matrix &net) {
    net = inputs.horizontalConcat(bias).multiply(weights);
    // CHANGE ACTIVATION FUNCTION AS NEEDED 
    Matrix out = Hyperbolic(net);
    return out;
}

Matrix Dataset::initializeWeights(double max_weight, int w, int h) {
    srand(time(NULL));

    vector<vector<double>> newarr (h, vector<double> (w));
    
    for (int i = 0; i < h; i++) {
        for (int j= 0; j < w; j++) {
            newarr[i][j] = ((double)rand())/(RAND_MAX+1.) * max_weight * 2 - max_weight;
        }
    }

    Matrix out(newarr);
    return out;
}

Dataset::~Dataset() {
    delete training_set;
    delete valid_set;
    delete test_set;
};
