#include "Header.h"

float* random_weights(int size) {

	// Create float random values between 0, 1 to create the weights
	// Randomize the seed
	srand(time(NULL));
	float *weights = (float*)malloc(size * sizeof(float));
	int i;

	// Save the wieghts
	for (i = 0; i < size; i++)
		weights[i] = (float)rand() / RAND_MAX;

	
	return weights;
}

float** random_data(int rows, int cols) {

	// Create the matrix pointers
	// Randomize the seed
	srand(time(NULL));

	float** data = (float**)malloc(rows * sizeof(float*));
	int i, j;

	// Allocate memory to the matrix
	for (i = 0; i < rows; i++)
		data[i] = (float*)malloc(cols * sizeof(float));

	// Create the random dataset
	for (i = 0; i < rows; i++)
		for(j = 0; j < cols-1; j++)
			if (i % 2 == 0) {
				data[i][j] = (float)rand() / RAND_MAX;
				data[i][cols - 1] = 0;
			}
			else {
				data[i][j] = ((float)rand() / RAND_MAX) * 10;
				data[i][cols - 1] = 1;
			}


	return data;
}

void dot_product(int width, int height, float* weight, float** data, float* bias, float alpha, int epochs) {

	// Calculate the dot product
	// i->width or rows, j->columns, y-> result
	int i, j, y, epoch = 0;
	float dot = 0.0;

	for (epoch = 0; epoch < epochs; epoch++)
		for (i = 0; i < height; i++){
			for (j = 0; j < width; j++)
				dot += weight[j] * data[i][j];
			dot += *bias;
			y = heaviside(dot); // Obtain a result
			
			// Update the weights and bias
			for (j = 0; j < width; j++)
				weight[j] += alpha * (data[i][width] - (float)y) * data[i][j];
			*bias += alpha * (data[i][width] - (float)y);
			dot = 0.0;
		}
}

int heaviside(float product) {

	// Calculate the heaviside function
	if (product >= 0)
		return 1;

	return 0;
}

float* class1_variables(float* class1, int size) {
	
	// Create a vector with class 1 data
	srand(time(NULL));
	class1 = (float*)malloc(size * sizeof(float));
	int i = 0;

	for (i = 0; i < size; i++)
		class1[i] = (float)rand() / RAND_MAX;

	return class1;
}

float* class2_variables(float* class2, int size) {

	// Create a vector with class 2 data
	srand(time(NULL));
	class2 = (float*)malloc(sizeof(float) * size);
	int i = 0;

	for (i = 0; i < size; i++)
		class2[i] = ((float)rand() / RAND_MAX) * 10;

	return class2;
}

int predict(float* weight, float* class1, float* bias, int size) {

	// Apply the dot product
	int i = 0;
	float result = 0;
	int prediction = 0;
	
	for (i = 0; i < size; i++)
		result += weight[i] * class1[i];

	result += *bias;
	prediction = heaviside(result);

	return prediction;
}