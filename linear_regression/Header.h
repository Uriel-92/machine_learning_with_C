#include <stdio.h>
#include <stdlib.h>
#include <time.h>


float* random_weights(int size = 2);
float** random_data(int rows = 20, int cols = 3);
void dot_product(int width, int height, float* weight, float** data, float* bias, float alpha = 0.2, int epochs = 100);
int heaviside(float product);
float* class1_variables(float* class1, int size);
float* class2_variables(float* class2, int size);
int predict(float* weight, float* class1, float* bias, int size);
