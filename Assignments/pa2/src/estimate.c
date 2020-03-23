/* PA2 estimate */

#include <stdio.h>
#include <stdlib.h>

void delete(long double **mat, int rows) {
	for (int i = 0; i < rows; i++) {
		free(mat[i]);
	}
	free(mat);
	}

void printMatrix(double **matrix,int rows, int cols) {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			printf("%f ", matrix[i][j]);
			if(j < rows - 1) {
				printf(" ");
			}
		}
		printf("\n");
	}
}

long double ** multiply(long double **matrix1, long double **matrix2, int row1, int col1, int row2, int col2) {
	long double **result = (long double**)malloc(sizeof(long double *) * row1);
	for(int i = 0; i < row1; i++) {
		result[i] = malloc(sizeof(long double) * col2);
	}
	for(int i = 0; i < row1; i++) {
		for(int j = 0; j < col2; j++) {
			result[i][j] = 0;
			for(int p = 0; p < col1; p++) {
				result[i][j] = result[i][j] + (matrix1[i][p] * matrix2[p][j]);
			}
		}
	}
	return result;
}


long double ** transpose(long double **matrix, int rows, int cols) {
	long double **result = (long double **)malloc(sizeof(long double *) * cols);
	for(int i = 0; i < cols; i++) {
		result[i] = malloc(sizeof(long double) * rows);
	}
	for(int i = 0; i < cols; i++) {
		for(int j = 0; j < rows; j++) {
			result[i][j] = matrix[j][i];
		}
	}
	return result;
}

long double ** invert(long double **matrix, int rows) {
	int r = rows;
	long double **identity = (long double **)malloc(sizeof(long double *) * r);
	for(int i = 0; i < r; i++) {
		identity[i] = malloc(sizeof(long double) * r);
	}
	for(int i = 0; i < r; i++) {
		identity[i][i] = 1.0;
	}

	for(int p = 0; p < r; p++) {
		long double pivot = matrix[p][p];
		for(int j = 0; j < r; j++) {
			matrix[p][j] = matrix[p][j] / pivot;
			identity[p][j] = identity[p][j] / pivot;
		}

		for(int i = (p + 1); i < r; i++) {
			pivot = matrix[i][p];
			for(int j = 0; j < r; j++) {
				matrix[i][j] = matrix[i][j] - (matrix[p][j] * pivot);
				identity[i][j] = identity[i][j] - (identity[p][j] * pivot);
			}
		}
	}
	long double pivot;
	for(int p = (r - 1); p >= 0; p--) {
		for(int i = (p - 1); i >= 0; i--) {
			pivot = matrix[i][p];
			for(int j = 0; j < r; j++) {
				matrix[i][j] = matrix[i][j] - (matrix[p][j] * pivot);
				identity[i][j] = identity[i][j] - (identity[p][j] * pivot);
			}
		}
	}
	matrix = identity;
	return matrix;
}

int main(int argc, char **argv) {

	if(argc < 3) {
		printf("Need to pass in input file!");
		return EXIT_SUCCESS;
	}

	char *filename = argv[1];
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror(filename);
		return 0;
	}

	char *filename2 = argv[2];
	FILE *fp2;
	fp2 = fopen(filename2, "r");
	if (fp2 == NULL) {
		perror(filename);
		return 0;
	}
	
	char buffer[100];
	fscanf(fp, "%s", buffer); 
//	puts(buffer);

	int attributes;
	fscanf(fp, "%d", &attributes);
	int houses;
	fscanf(fp, "%d", &houses);

	int actualcols = attributes + 1;
	long double **dummymatrix = (long double **)malloc(sizeof(long double *) * (houses));
	for(int i = 0; i < houses; i++) {
		dummymatrix[i] = (long double *)malloc(sizeof(long double) * actualcols);
	}

	for(int k = 0; k < houses; k++) {
		for(int l = 0; l < actualcols; l++) {
			long double num;
			fscanf(fp, "%Lf", &num);
			dummymatrix[k][l] = num;
		}
	}	

	// ORIGINAL MATRIX //
	long double **matrix = (long double **)malloc(sizeof(long double *) * (houses));
	for(int i = 0; i < houses; i++) {
		matrix[i] = (long double *)malloc(sizeof(long double) * actualcols);
	}

	for(int k = 0; k < houses; k++) {
		matrix[k][0] = 1.0;
	}

	for(int k = 0; k < houses; k++) {
		for(int l = 1; l < actualcols; l++) {
			matrix[k][l] = dummymatrix[k][l-1];
		}
	}
	// ORIGINAL MATRIX //

	
	// PRICES //
	long double **prices = (long double **)malloc(sizeof(long double *) * (houses));
	for(int i = 0; i < houses; i++) {
		prices[i] = (long double *)malloc(sizeof(long double) * 1);
	}
	for(int k = 0; k < houses; k++) {
		prices[k][0] = dummymatrix[k][actualcols - 1];
	}
	// PRICES //

	// INVERTIBLE MATRIX COMPUTATION //
	long double **inverse = (long double **)malloc(sizeof(long double *) * actualcols);
	for(int i = 0; i < actualcols; i++) {
		inverse[i] = (long double *)malloc(sizeof(long double) * houses);
	}

	inverse = transpose(matrix, houses, actualcols);
	inverse = multiply(inverse, matrix, actualcols, houses, houses, actualcols);
	inverse = invert(inverse, actualcols);
	// INVERTIBLE MATRIX COMPUTATION //

	// CALCULATING THE W FROM TRAINING DATA //
	matrix = transpose(matrix, houses, actualcols);
	inverse = multiply(inverse, matrix, actualcols, actualcols, actualcols, houses);
	matrix = multiply(inverse, prices, actualcols, houses, houses, 1);	
	// CALCULATING THE W FROM TRAINING DATA //

	char buffer2[100]; 
	fscanf(fp2, "%s", buffer2);
//	puts(buffer2);

	int attributes2;
	fscanf(fp2, "%d", &attributes2);
	int houses2;
	fscanf(fp2, "%d", &houses2);
	
	int actualcols2 = attributes2 + 1;
	long double **data = (long double **)malloc(sizeof(long double *) * houses2);
	for(int i = 0; i < houses2; i++) {
		data[i] = (long double *)malloc(sizeof(long double) * actualcols2);
	}
	for(int i = 0; i < houses2; i++) {
		data[i][0] = 1;
	}
	for(int i = 0; i < houses2; i++) {
		for(int j = 1; j < actualcols2; j++) {
			long double num2;
			fscanf(fp2, "%Lf", &num2);
			data[i][j] = num2;
		}
	}
	
	data = multiply(data, matrix, houses2, actualcols2, actualcols, 1);
	for(int i = 0; i < houses2; i++) {
		double p = data[i][0];
		printf("%.0f\n",p);
	}

	fclose(fp);
	fclose(fp2);

	delete(dummymatrix,houses);
	delete(prices, houses);
	delete(data, houses2);
	delete(matrix, actualcols);
	delete(inverse, actualcols);

	return EXIT_SUCCESS;
}
