#include <stdio.h>
#include <stdlib.h>

void add_matrices(char* filepath1, char* filepath2, char* result_filepath) {
    FILE *file1, *file2, *result_file;
    unsigned int rows1, cols1, rows2, cols2;

    // Open the first input file
    file1 = fopen(filepath1, "rb");
    if (file1 == NULL) {
        perror("Error opening file1");
        return;
    }

    // Read the dimensions of the first matrix
    fread(&rows1, sizeof(unsigned int), 1, file1);
    fread(&cols1, sizeof(unsigned int), 1, file1);

    // Allocate memory for the first matrix
    int *matrix1 = (int *)malloc(rows1 * cols1 * sizeof(int));
    if (matrix1 == NULL) {
        perror("Memory allocation failed for matrix1");
        fclose(file1);
        return;
    }

    // Read the elements of the first matrix
    fread(matrix1, sizeof(int), rows1 * cols1, file1);
    fclose(file1);

    // Open the second input file
    file2 = fopen(filepath2, "rb");
    if (file2 == NULL) {
        perror("Error opening file2");
        free(matrix1);
        return;
    }

    // Read the dimensions of the second matrix
    fread(&rows2, sizeof(unsigned int), 1, file2);
    fread(&cols2, sizeof(unsigned int), 1, file2);

    // Check if the dimensions match
    if (rows1 != rows2 || cols1 != cols2) {
        fprintf(stderr, "Matrix dimensions do not match.\n");
        fclose(file2);
        free(matrix1);
        return;
    }

    // Allocate memory for the second matrix
    int *matrix2 = (int *)malloc(rows2 * cols2 * sizeof(int));
    if (matrix2 == NULL) {
        perror("Memory allocation failed for matrix2");
        fclose(file2);
        free(matrix1);
        return;
    }

    // Read the elements of the second matrix
    fread(matrix2, sizeof(int), rows2 * cols2, file2);
    fclose(file2);

    // Allocate memory for the result matrix
    int *result_matrix = (int *)malloc(rows1 * cols1 * sizeof(int));
    if (result_matrix == NULL) {
        perror("Memory allocation failed for result_matrix");
        free(matrix1);
        free(matrix2);
        return;
    }

    // Perform matrix addition
    for (unsigned int i = 0; i < rows1 * cols1; ++i) {
        result_matrix[i] = matrix1[i] + matrix2[i];
    }

    // Open the result file
    result_file = fopen(result_filepath, "wb");
    if (result_file == NULL) {
        perror("Error opening result file");
        free(matrix1);
        free(matrix2);
        free(result_matrix);
        return;
    }

    // Write the dimensions of the result matrix
    fwrite(&rows1, sizeof(unsigned int), 1, result_file);
    fwrite(&cols1, sizeof(unsigned int), 1, result_file);

    // Write the elements of the result matrix
    fwrite(result_matrix, sizeof(int), rows1 * cols1, result_file);
    fclose(result_file);

    // Free allocated memory
    free(matrix1);
    free(matrix2);
    free(result_matrix);
}
