//
// Created by jarvis on 19/8/18.
//

#ifndef CA_LAB_MATRIX_MULTIPLICATION_H
#define CA_LAB_MATRIX_MULTIPLICATION_H

void run_matrix_multiplication(){
//    int matrices[TOTAL_MATRICES][MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    int matrix1[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    int matrix2[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
//    int matrices[TOTAL_MATRICES];
    int row_lis[TOTAL_MATRICES];
    int col_lis[TOTAL_MATRICES];
    printf("Matrix\nsize: ");
    scanf("%d %d", &row_lis[0], &col_lis[0]);
    get_matrix_values(matrix1, row_lis[0], col_lis[0]);
    printf("Matrix\nsize: ");
    scanf("%d %d", &row_lis[1], &col_lis[1]);
    get_matrix_values(matrix2, row_lis[1], col_lis[1]);
    display_matrix(matrix1, row_lis[0], col_lis[0]);
    display_matrix(matrix2, row_lis[1], col_lis[1]);
    matrix_multiply(matrix1, matrix2, row_lis[0], col_lis[0], row_lis[1], col_lis[1]);
}

#endif //CA_LAB_MATRIX_MULTIPLICATION_H
