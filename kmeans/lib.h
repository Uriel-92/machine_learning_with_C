#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

float** distance(float** data, float* centroids, int len, int width, int numCentroids);
float** generateCentroids(int numCentroides, int numFeatures);
float** randomNumbers(int len, int numFeatures);
int* argMin(float** distances, int len, int width);
float** newCentroids(float** data, int* labels, int len, int width, int numCentroids);

