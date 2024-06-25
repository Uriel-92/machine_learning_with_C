#include "class.hpp"
#include <ctime>
#include <cstdlib>

using namespace std;

float** matrix(int rows, int cols){
    float** values = new float* [rows];

    for (int i = 0; i < rows; i++)
        values[i] = new float[cols];

    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            if(i < 5){
                values[i][j] = (float)(rand()) / (RAND_MAX);
            }
            else {
                values[i][j] = (float)(rand()) / (RAND_MAX) + 5;
            }

    return values;
}

int main(int argc, char* argv[])
{
    int* classes = new int[2];
    classes[0] = 0;
    classes[1] = 1;
    int rows = 10;
    int cols = 2;
    int* y = new int[10];
    y[0] = 0; y[1] = 0; y[2] = 0; y[3] = 0; y[4] = 0;
    y[5] = 1; y[6] = 1; y[7] = 1; y[8] = 1; y[9] = 1;
    float** values = matrix(rows, cols);
    float test[2] = {0.156, 0.12345};
    float test1[2] = { 8.1, 5.2 };

    naiveBayes z(values, y, classes, rows, cols);

    z.fit();
    cout << z.predict(test) << endl;
    cout << z.predict(test1) << endl ;

    return 0;
}
