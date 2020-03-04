/* CS 211 PA1: mexp
 * Created for: fk206
 */

#include <stdio.h>
#include <stdlib.h>

 void PrintMatrix(int **matrix, int size) {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			printf("%d", matrix[i][j]);
			if(j < size - 1) {
				printf(" ");
			}
		}
		printf("\n");
	}
	return;
} 

int** Multiply(int **matrix1, int **matrix2, int size) {
	int **result = malloc(sizeof(int *) * size);
	for (int i = 0; i < size; i++) {
		result[i] = malloc(sizeof(int) * size);
	}
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			result[i][j] = 0;
			for(int p = 0; p < size; p++) {
				result[i][j] = result[i][j] + (matrix1[i][p] * matrix2[p][j]);
			}
		}
	} 
	return result;
}

int main(int argc, char **argv) {

	if (argc < 2) {
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

	int size;
	fscanf(fp,"%d", &size);
	int **matrix = (int **)malloc(sizeof(int *) * size); 

	for(int i = 0; i < size; i++) {
		matrix[i] = (int *)malloc(sizeof(int) * size);
	}
	
	for(int k = 0; k < size; k++) {
		for(int l = 0; l < size; l++) {
			int num;
			fscanf(fp,"%d", &num);
			matrix[k][l] = num;
		}
	}

	int power;
	fscanf(fp,"%d",&power);
	fclose(fp);
	int **result = matrix;
	
//	int resultant;

//	int **final = matrix;

//	printf("The size of the matrix is %d, the first value of the matrix is %d, the last value of the matrix is %d, and the power of the matrix is %d", size, result[0][0], result[size-1][size-1], power);

	result = Multiply(matrix,matrix,size);
	power--;
	while(power > 1) {
		result = Multiply(result,matrix,size);
		power--;
	}
//	printf("\n\n");
	PrintMatrix(result, size);
	
    return EXIT_SUCCESS;
}
