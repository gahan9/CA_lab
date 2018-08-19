//
// Created by jarvis on 17/8/18.
//

#ifndef CA_LAB_UTILITY_H
#define CA_LAB_UTILITY_H

#include <stdio.h>
#include <stdarg.h>
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

void display_matrix(int *array, int row, int col){
    // display given array of given size(no. of elements require because sizeof() returns max bound value)
    write_log("%d x %d matrix:\n", row, col);
    static int i, j;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++) {
            write_log("%d ", *((array + i*col) + j));
        }
        write_log("\n");
    }
}

int matrix_multiply(int *matrix1, int *matrix2, int row1, int col1, int row2, int col2){
    if(col1 != row2){
        printf("Invalid order or matrix multiplication not possible");
        return 0;
    }
    else{
        int result[row1][col2];
        display_matrix(matrix1, row1, col1);
        display_matrix(matrix2, row2, col2);
//        for(int i=0; i < row1; i++){
//            for(int j=0; j < col2; j++){
//                write_log("%d x %d", *(matrix1 + i*col1 + j), *(matrix2 + j*col2 + i));
////                result[i][j] += (*(matrix1 + i*col1 + j)) * (*(matrix2 + j*col2 + i));
//            }
//        }
        display_matrix(result, row1, col2);
        return result;
    }
}

#endif //CA_LAB_UTILITY_H
