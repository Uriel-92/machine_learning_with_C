/* Main script*/
#include "functions.h"

struct {
    float** data = NULL;
    int* labels_class0 = NULL;
    int* labels_class1 = NULL;
}list;


int main(){
    int num_samples = 10;
    int num_features = 2;
    int* labels_class0 = NULL;
    int* labels_class1 = NULL;
    int class0 = 10000;
    int class1 = 10000;
    float** sample_class0 = NULL;
    float** sample_class1 = NULL;
    float* distance_class0 = NULL;
    float* distance_class1 = NULL;

    /* Generate dataset and labels */
    list.data = random_numbers(num_samples, num_features);
    list.labels_class0 = generate_labels(num_samples);
    list.labels_class1 = generate_labels(num_samples);

    /* Generate Sample */
    sample_class0 = generateSample(1, num_features);
    sample_class1 = generateSample(1, num_features, false);

    /* Calculate the distance */
    distance_class0 = distances(list.data, sample_class0, 1, num_samples, num_features);
    distance_class1 = distances(list.data, sample_class1, 1, num_samples, num_features);

    /* Sort labels according to the distances */
    labels_class0 = sortLabels(distance_class0, list.labels_class0, num_samples);
    labels_class1 = sortLabels(distance_class1, list.labels_class1, num_samples);

    /* Print labels */
    cout<<"Labels class 0"<<endl;
    for(int i=0; i<num_samples; i++)
        cout<<labels_class0[i]<<endl;
    
    cout<<"Labels class 1"<<endl;
    for(int i=0; i<num_samples; i++)
        cout<<labels_class1[i]<<endl;   

    class0 = inference(labels_class0, num_features, 3, num_features);
    class1 = inference(labels_class1, num_features, 3, num_features);

    /* Print the result */
    cout<<"Class 0 result: "<<class0<<endl;
    cout<<"Class 1 result: "<<class1<<endl;

    /* Clean the memory */
    for(int i=0; i<num_samples; i++)
        delete[] list.data[i];
    
    for(int i=0; i<1; i++){
        delete[] sample_class0[i];
        delete[] sample_class1[i];
    }

    delete[] sample_class0;
    delete[] sample_class1;
    delete[] labels_class0;

    return 0;
}