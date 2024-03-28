/* Script that containt the functions nedeed to create knn */
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/* Function to generate random numbers for different classes*/
float** random_numbers(int num_samples, int num_features){
    /* Initialize the data */
    float** data = new float* [num_samples];
    for(int i=0; i<num_samples; i++)
        data[i] = new float [num_features];

    /* Initialize the data */
    for(int i=0; i<num_samples; i++)
        for(int j=0; j<num_features; j++)
            if(j%2 == 0)
                data[i][j] = (float)rand()/RAND_MAX;
            else
                data[i][j] = (float)rand()/ RAND_MAX * 6;

    return data;
}

/* Function to generate labels */
int* generate_labels(int num_samples){
    /* Initialize the labels */
    int* labels = new int[num_samples];

    for(int i=0; i<num_samples; i++)
        if(i%2 == 0)
            labels[i] = 0;
        else
            labels[i] = 1;
    
    return labels;
}

/* Generate one point */
float** generateSample(int numSamples, int len, bool jump=true){
    float** sample = new float*[1];

    for(int i=0; i<numSamples; i++)
        sample[i] = new float[len];

    for(int i=0; i<numSamples; i++)
        for(int j=0; j<len; j++)
            if(jump)
                sample[i][j] = (float) rand()/RAND_MAX;
            else
                sample[i][j] = (float)rand()/ RAND_MAX * 6;
    
    return sample;
}


/* Meassure the distance between the data and one sample */
float* distances(float** data, float** point, int lenPoint, int numSamples, int numFeatures){
    float* dist = new float[numSamples];
    float count = 0;
    
    for(int k=0; k<lenPoint; k++){
        for(int i=0; i<numSamples; i++){
            for(int j=0; j<numFeatures; j++){
                count += pow((data[i][j] - point[k][j]),2);
            }
            dist[i] = sqrt(count);
            count = 0;
        }
    }

    return dist;
}

/* Sort labels according to the distance */
int* sortLabels(float* distance, int* labels, int numSamples){
    int* labels_sample = labels;
    float number;
    int label;

    for(int i=0; i<numSamples; i++){
        for(int j=i+1; j<numSamples; j++){
            if(distance[j] < distance[i]){
                /* Sort numbers */ 
                number = distance[i];
                distance[i] = distance[j];
                distance[j] = number;

                /* Sort labels */
                label = labels_sample[i];
                labels_sample[i] = labels_sample[j];
                labels_sample[j] = label;
            }
        }
    }

    return labels_sample;
}

/* Infer the label according to the new point */
int inference(int* labels, int len, int numNeighbors, int numFeatures){
    int label;
    float data[numFeatures];
    float max = -1000;

    for(int k=0; k<numFeatures; k++)
        data[k] = 0;

    for(int k=0; k<numFeatures; k++){
        for(int i=0; i<numNeighbors; i++){
            if(labels[i] == k){
                data[k] += 1;
            }
        }
    }

    for(int k=0; k<numFeatures; k++){
        if(data[k]>max){
            max = data[k];
            label = k;
        }
    }

    return label;
}