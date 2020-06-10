#include "Dataset.h"

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
        cout << file_name << " opened!\n";
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
    else {
        cout << "WARNING: set name is invalid\n";
    }

    file.close();
}

Matrix Dataset::feedForward(Matrix inputs, Matrix weights, Matrix bias, Matrix &net) {
    net = inputs.horizontalConcat(bias).multiply(weights);
    // CHANGE ACTIVATION FUNCTION AS NEEDED 
    Matrix out = Hyperbolic(net);
    return out;
}

Matrix Dataset::initializeWeights(double max_weight, int w, int h) {
    srand(time(NULL));

    vector<vector<double>> newarr (h, vector<double> (w));
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            // random number between [-max_weight, max_weight]
            // change rand() (which returns integral value from 0 to RAND_MAX) to a fraction; range is [0, 1]
            // transform using x * (2weight) - weight to change range to [-weight, weight]
            newarr[i][j] = ((double)rand())/(RAND_MAX+1.) * max_weight * 2 - max_weight;
        }
    }

    Matrix out(newarr);
    return out;
}

void Dataset::evalError(Matrix inputs, Matrix weights, Matrix output, Matrix mat_class, Matrix bias, double &error, double &c_error, int samples) {
    Matrix &net = * (new Matrix()); // dummy matrix to compute net
    Matrix Z = feedForward(inputs, weights, bias, net);
    delete &net;

    // error
    error = (Z.add(output.scalarMultiply(-1))).sumElements(2) / (samples * output_count);
    
    // classification error
    Matrix classes = Z.toClass();
    c_error = classes.difference(mat_class) / ((double) samples);
}

void Dataset::evalErrorSet(SetWrapper set_w, Matrix weights, double &error, double &c_error) {
    Matrix &net = * (new Matrix()); // dummy matrix to compute net
    Matrix Z = feedForward(set_w.inputs, weights, set_w.bias, net);
    delete &net;

    // error
    error = Z.add(set_w.outputs.scalarMultiply(-1)).sumElements(2) / (set_w.count * output_count);
    
    // classification error
    Matrix classes = Z.toClass();
    c_error = classes.difference(set_w.classes) / ((double) set_w.count);
}

void Dataset::backprop(Matrix inputs, Matrix &weights, Matrix outputs, double alpha, Matrix bias) {
    int row = (int) rand()/(RAND_MAX+1.)*training_set->count;
    // int row = 4;
    Matrix sampleInput = inputs.row(row);
    Matrix sampleOutput = outputs.row(row);
    Matrix sampleBias = bias.row(row);

    Matrix &net = * (new Matrix());
    Matrix out = feedForward(sampleInput, weights, sampleBias, net);

    Matrix error_vector = sampleOutput.add(out.scalarMultiply(-1));
    Matrix delta = error_vector.Hadamard(HyperbolicPrime(net));

    Matrix inputBias = sampleInput.horizontalConcat(sampleBias);
    Matrix weights_delta = delta.Kronecker(inputBias.transpose());
    
    weights_delta = weights_delta.scalarMultiply(alpha);
    weights = weights.add(weights_delta.transpose());
    delete &net;
}

Matrix Dataset::train(vector<vector<double>> &errors) {

    Matrix weights = initializeWeights(0.5, output_count, input_count+1); // generate random weights
    double alpha = 0.1; // learning rate

    int epochs = 0;
    int MAX_EPOCHS = 100;

    while (epochs <= MAX_EPOCHS) {
        double e, ce;
        vector<double> errs(6, 0);
        cout << "epochs: " << epochs << "\n";
        backprop(training_set->inputs, weights, training_set->outputs, alpha, training_set->bias);
        cout << "epochs: eval! " << epochs << "\n";
        evalErrorSet(*training_set, weights, errs[0], errs[1]);
        evalErrorSet(*valid_set, weights, errs[2], errs[3]);
        evalErrorSet(*test_set, weights, errs[4], errs[5]);

        errors.push_back(errs);    

        epochs++;
    }

    return weights;
}

Dataset::~Dataset() {
    delete training_set;
    delete valid_set;
    delete test_set;
};
