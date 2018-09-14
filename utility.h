//
// Created by jarvis on 17/8/18.
//

#ifndef CA_LAB_UTILITY_H
#define CA_LAB_UTILITY_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
//extern int DEBUG;

int write_log(const char *format, ...) {
    if(DEBUG) {
        va_list args;
        va_start (args, format);
        vprintf(format, args);
        va_end (args);
    }
}

int *get_min_max(int *array, int no_of_elements, int min_max[]){
    // get minimum and maximum of array
//    printf("elements of array: ");
    for(int i=0; i<no_of_elements; i++){
//        printf("%d ", *(array + i));
        if (*(array + i) < min_max[0])
            min_max[0] = *(array + i);
        if (*(array + i) > min_max[1])
            min_max[1] = *(array + i);
    }
    return min_max;
}

void display_matrix(double array[][MAX_MATRIX_SIZE], int row, int col){
    // display given array of given size(no. of elements require because sizeof() returns max bound value)
    write_log("%d x %d matrix:\n", row, col);
    static int i, j;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++) {
            write_log("%lf ", array[i][j]);
        }
        write_log("\n");
    }
}

void get_matrix_values(double array[][MAX_MATRIX_SIZE], int row, int col, int user_input){
    // display given array of given size(no. of elements require because sizeof() returns max bound value)
//    write_log("%d x %d matrix:\n", row, col);
    static int i, j;
    if (user_input) {
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                printf("[%d][%d]: ", i, j);
                scanf("%lf", &array[i][j]);
            }
        }
    }
}

void matrix_multiply(double matrix1[][MAX_MATRIX_SIZE], double matrix2[][MAX_MATRIX_SIZE], int row1, int col1, int row2, int col2){
    clock_t t;
    double cpu_time_consumption;
    if(col1 != row2){
        printf("Invalid order or matrix multiplication not possible");
    }
    else{
        double result[][MAX_MATRIX_SIZE] = {{0}};
        int i, j, k;
        t = clock();
        #pragma omp parallel for
        for(i=0; i < row1; i++){
            for(j=0; j < col2; j++){
//                write_log("[%d][%d]-> %d x %d\n", i, j, matrix1[i][j], matrix2[j][i]);
                for(k=0; k < col1; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        t = clock() - t;
        cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
        printf("\n>>:: %f\n", cpu_time_consumption);
        display_matrix(result, row1, col2);
//        return result;
    }
}

#endif //CA_LAB_UTILITY_H
