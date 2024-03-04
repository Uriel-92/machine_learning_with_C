#include "functions.h"


int main(){

    int width = 2;
    int height = 10;
    int numCentroids = 2;
    srand(time(0));

    float** data = randomNumbers(height, width);
    float** centroids = generateCentroids(numCentroids, width);
    int* labels = NULL;

    Kmeans kmeans(data, centroids, height, width, numCentroids);
    labels = kmeans.fit();

    for(int i=0; i<height; i++)
        cout<<labels[i]<<endl;

    
    // Free memory
    for(int i=0; i<height; i++)
        delete[] data[i];

    for(int i=0; i<numCentroids; i++)
        delete[] centroids[i];

    delete[] data;
    delete[] centroids;
    delete[] labels;

    return 0;
}