#include "Dataset.h"

using namespace std;

void testIO() {
    ifstream file;
    file.open("test.dat");
    SetWrapper *test = new SetWrapper();
    // while (!file.eof()) {
    //     double x;
    //     file >> x;
    //     cout << x << "\n";
    // }
    test->read(file, 4, 3);
    test->inputs.print();
    cout << "\n";
    test->outputs.print();
    cout << "\n";
    test->classes.print();
    cout << "\n";
    test->bias.print();
    file.close();
}

void workingOpen() {
    Dataset ds (4, 2);
    ds.createSet("test_data/train.dat", "train");
    Matrix i = ds.training_set->inputs;
    Matrix o = ds.training_set->outputs;
    Matrix b = ds.training_set->bias;
    Matrix c = ds.training_set->classes;
    int count = ds.training_set->count;

    i.print();
    printf("a\n");
    o.print();
    printf("b\n");
    b.print();
    printf("c\n");
    c.print();
    printf("\n\n%d", count);
}

void kron() {
    vector<vector<double>> A = {{1, 2}};
    vector<vector<double>> B = {{3}, {7}, {8}, {9}, {11}};
    Matrix a(A);
    Matrix b(B);
    Matrix x = a.Kronecker(b);
    x.print();
}

int main() {

    Dataset ds (4, 2);
    ds.createSet("test_data/train.dat", "train");
    ds.createSet("test_data/valid.dat", "valid");
    ds.createSet("test_data/test.dat", "test");

    // use errors vector<vector<double>>, convert to matrix, use Matrix.toFile(fileName)

    vector<vector<double>> errors;
    printf("Start Training\n");
    Matrix w = ds.train(errors);
    printf("Training Done!\n");
    Matrix errors_mat(errors);

    errors_mat.toFile("errors3.dat");
    printf("\nFinished!");
    return 0;
}