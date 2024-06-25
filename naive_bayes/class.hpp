#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class statistic {
public:

	statistic() {}

	float* meanCalculation (float** matrix, int rows, int cols, int axis) {
		float* mean = NULL;
		
		if (axis == 0) {
			mean = new float[cols];
			for (int i = 0; i < cols; i++)
				mean[i] = 0;
			for (int i = 0; i < cols; i++)
				for (int j = 0; j < rows; j++)
					mean[i] += matrix[j][i] / (rows * cols);
			
		}
		else if (axis == 1) {
			mean = new float[rows];
			for (int i = 0; i < rows; i++)
				mean[i] = 0;
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					mean[i] += matrix[i][j] / (rows * cols);
		}

		return mean;
	}

	float* varCalculation(float** matrix, int rows, int cols,int  axis) {
		float* var = NULL;
		float* mean = meanCalculation(matrix, rows, cols, axis);

		if (axis == 0) {
			var = new float[cols];
			for (int i = 0; i < cols; i++)
				var[i] = 0;
			for (int i = 0; i < cols; i++)
				for (int j = 0; j < rows; j++)
					var[i] += pow((matrix[j][i] - mean[i]), 2) / (rows * cols);
		}
		else if (axis == 1) {
			var = new float[rows];
			for (int i = 0; i < rows; i++)
				var[i] = 0;
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					var[i] += pow((matrix[i][j] - mean[i]), 2) / (rows * cols);
		}

		return var;

	}

	float** zerosArray(int rows, int cols) {
		float** values = new float* [rows];

		for (int i = 0; i < rows; i++)
			values[i] = new float [cols];

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				values[i][j] = 0;


		return values;
	}

	float* zeroArray(int rows) {
		float* values = new float [rows];

		
		for (int i = 0; i < rows; i++)
			values[i] = 0;

		return values;

	}

	float** classSearch(float** matrix, int rows, int cols, int* labels, int label) {
		int num_samples = 0;

		for (int i = 0; i < rows; i++)
			if (labels[i] == label)
				num_samples += 1;

		float** values = new float* [num_samples];

		for (int i = 0; i < num_samples; i++)
			values[i] = new float[cols];

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (labels[i] == label)
					values[i][j] = matrix[i][j];


		return values;
	}

};


class naiveBayes {


public:

	int* classes = NULL;
	int numClasses = 2;
	float** mean = NULL;
	float** var = NULL;
	float* priors = NULL;
	float** values = NULL;
	int* y = NULL;
	int rows, cols = 0;


	naiveBayes(float** values, int* y, int* classes, int rows, int cols) {
		this->classes = classes;
		this->values = values;
		this->y = y;
		this->rows = rows;
		this->cols = cols;
		statistic a;
		mean = a.zerosArray(2, cols);
		var = a.zerosArray(2, cols);
		priors = a.zeroArray(2);

	}

	~naiveBayes() {
		for (int i = 0; i < cols; i++) {
			delete[] mean[i];
			delete[] var[i];
			delete[] values[i];
		}

		delete[] mean;
		delete[] var;
		delete[] values;
		delete[] priors;
		delete[] y;
		delete[] classes;
	}

	void fit(void) {

		float** matrix = NULL;
		statistic a;
		float* tmp = a.zeroArray(cols);

		for (int i = 0; i < numClasses; i++) {
			matrix = indexing(i);
			tmp = a.meanCalculation(matrix, 5, cols, 0);
			mean[i][0] = tmp[0];
			mean[i][1] = tmp[1];
			tmp = a.varCalculation(matrix, 5, cols, 0);
			var[i][0] = tmp[0];
			var[i][1] = tmp[1];
			priors[i] = (float) size(i) / rows;
			tmp = a.zeroArray(cols);
		}

	}

	int predict(float* x) {
		float* y_pred = new float[cols];
		for (int i = 0; i < cols; i++)
			y_pred[i] = 0;
		float posterior = 0;
		float prior = 0;

		for (int i = 0; i < numClasses; i++) {
			prior = log(priors[i]);
			posterior = sumLog(i, x);
			posterior = posterior + prior;
			y_pred[i] = posterior;
		}

		return argMax(y_pred);
	}
	

	float** indexing(int label) {
		float** matrix = NULL;
		int size = 0;
		int k = 0;
		bool flag = false;

		for (int i = 0; i < rows; i++) {
			if (y[i] == label)
				size += 1;
		}

		matrix = new float* [size];
		for (int i = 0; i < size; i++)
			matrix[i] = new float[cols];

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (y[i] == label) {
					matrix[k][j] = values[i][j];
					flag = true;
				}
			}
			if (flag) {
				k += 1;
				flag = false;
			}
		}

		return matrix;
	}

	int size(int label) {
		int tam = 0;

		for (int i = 0; i < rows; i++) {
			if (y[i] == label)
				tam += 1;
		}

		return tam;

	}

private:

	float sumLog(int i, float* vector) {
		float numerator = 0, denominator = 0, result = 0;


		for (int j = 0; j < cols; j++) {
			numerator = exp(-(pow(vector[j] - mean[i][j], 2)) / (2 * var[i][j]));
			denominator = sqrt(2 * M_PI * var[i][j]);
			result += log(numerator / denominator);
		}
		
		return result;
	}

	int argMax(float* y_pred) {
		int indx = 0;
		float value = -100000;

		for (int i = 0; i < cols; i++)
			if (y_pred[i] > value){
				value = y_pred[i];
				indx = i;
			}

		return indx;
	}

};
