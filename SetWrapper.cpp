#include "SetWrapper.h"

using namespace std;

SetWrapper::SetWrapper() {

}

void SetWrapper::read(ifstream &file, int input_count, int output_count) {
    vector<vector<double>> input_array;
    vector<vector<double>> output_array;    
    count = 0;

    while (!file.eof()) {
        // get input features
        vector<double> in_array(input_count);
        for (int i = 0; i < input_count; i++) {
            file >> in_array[i];
        }
        input_array.push_back(in_array);

        // get class number
        int class_num;
        file >> class_num;
        vector<double> out_array(output_count, 0);
        // one-hot encoding in row form
        out_array[class_num] = 1;
        output_array.push_back(out_array);

        // increaes the number of examples in this dataset
        count++;
    }
    
    vector<vector<double>> bias_array (count, vector<double> (1, 1));

    inputs = * (new Matrix(input_array));
    outputs = * (new Matrix(output_array));
    classes = outputs.toClass();
    bias = * (new Matrix(bias_array));
}


SetWrapper::~SetWrapper() {

}