#include "Header.h"

int  main() {

	
	// Test random values, size by default = 2
	float* w = NULL;
	float bias = 0.1;
	float** data = NULL;
	int rows = 100;
	int cols = 7;
	float* cls1 = NULL;
	float* cls2 = NULL;


	w = random_weights(cols);
	int i, j;

	// Print the wieghts
	for (i = 0; i < cols; i++)
		printf("Random weights = %.4f\n", w[i]);

	
	// Create a random dataset and generate a matrix with the values.
	// The last column are the labels
	data = random_data(rows, cols);

	// Check the values
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++)
			printf("%.4f ", data[i][j]);
		printf("\n");
	}

	// Dot_product and evaluation
	dot_product(cols-1, rows, w, data, &bias);

	// Print the wieghts after the training
	for (i = 0; i < cols; i++)
		printf("Weights after the training = %.4f\t", w[i]);
	printf("\n");

	// Test with new data
	// Create two variables with class 1 -> 1 and class 2 -> 0
	cls1 = class1_variables(cls1, cols-1);
	cls2 = class2_variables(cls2, cols-1);
	
	// Predict classes
	printf("Class1 predict %d\n", predict(w, cls1, &bias, cols-1));
	printf("Class2 predict %d\n", predict(w, cls2, &bias, cols-1));
	// Eureka!!! Archimedes said

	free(w);
	free(cls1);
	free(cls2);
	free(data);
	return 0;
}