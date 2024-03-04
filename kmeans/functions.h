#include "lib.h"

using namespace std;

float** distance(float** data, float** centroids, int len, int width, int numCentroids){
    // Control variables
    float** dist = new float* [len];
    int i, j, k;
    float count = 0.0;

    for(i = 0; i < len; i++)
        dist[i] = new float [width];

    for(k = 0; k < numCentroids; k++)
        for(i = 0; i < len; i++){
            for(j = 0; j < width; j++){
                count = count + pow(centroids[k][j] - data[i][j], 2);
            }
            dist[i][k] = sqrt(count);
            count = 0.0;
        }

    return dist;
}

float** randomNumbers(int len, int numFeatures){
    float** numbers = new float* [len];
    int i, j = 0;

    for(i = 0; i < len; i++)
        numbers[i] = new float [numFeatures];

    for(i = 0; i < len; i++)
        for(j = 0; j < numFeatures; j++)
            if(i%2 == 0){
                numbers[i][j] = (float)rand()/RAND_MAX;
            }
            else{
                numbers[i][j] = ((float)rand()/RAND_MAX) * 10;
            }
    
    return numbers;
}

float** generateCentroids(int numCentroides, int numFeatures){
    float **centroids = new float* [numCentroides];
    int i, j = 0;

    for(i=0; i<numCentroides; i++)
        centroids[i] = new float [numFeatures];
    
    for(i=0; i<numCentroides; i++)
        for(j=0;j<numFeatures; j++)
            if(i%2 == 0){
                centroids[i][j] = (float)rand()/RAND_MAX;
            }
            else{
                centroids[i][j] = ((float)rand()/RAND_MAX) * 2;
            }
    
    return centroids;

}

int* argMin(float** distances, int len, int width){
    int i, j, label;
    float minimum = 10000.0;
    int* labels = new int [len];
    float* array = new float [width];

    for(i=0; i<len; i++){
        for(j=0; j<width; j++){
            array[j] = distances[i][j];
        }
        for(int k=0; k<width; k++)
            if(array[k] < minimum){
                minimum = array[k];
                label = k+1;
            }
        labels[i] = label;
        minimum = 10000.0;
        label = 0;
    }

    return labels;
}

float** newCentroids(float** data, int* labels, int len, int width, int numCentroids){
    float** centroids = new float* [numCentroids];
    for(int i=0; i<numCentroids; i++)
        centroids[i] = new float [numCentroids];
    
    int label = 1;
    float x = 0;
    float y = 0;
    int count = 0;

    for(int k=0; k<numCentroids; k++){
        for(int i=0; i<len; i++){
            for(int j=0; j<width; j++){
                if(labels[i] == label){
                    if(j==0)
                        x += data[i][j];
                    else
                        y += data[i][j];
                    count ++;
                }
            }
            
        }
        centroids[k][0] = x/count;
        centroids[k][1] = y/count;
        x = 0;
        y = 0;
        labels ++;
        count = 0;
    }

    return centroids;
}

class Kmeans{
    public:
    float **data = NULL;
    float **centroids = NULL;
    int iterations = 0;
    int len = 0;
    int width = 0;
    int numCentroids = 0;
    int* labels = NULL;
    float** dist;
    
    public:
    Kmeans(float **data, float **centroids, int len, int width, int numCentroids, int iterations=1000){
        this->data = data;
        this->centroids = centroids;
        this->iterations = iterations;
        this->len = len;
        this->width = width;
        this->numCentroids = numCentroids;
        this->iterations = iterations;
    }

    public:
    int* fit(){
        int i=0;
        int j=0;
        for(i=0; i < iterations; i++){
            dist = distance(data, centroids, len, width, numCentroids);
            labels = argMin(dist, len, width);
            centroids = newCentroids(data, labels, len, width, numCentroids);
        }

        for(int i=0; i<len; i++)
            delete[] dist[i];
        
        delete[] dist;
        return labels;
    }
};