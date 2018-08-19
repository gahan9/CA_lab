#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <graphics.h>
#include "constant.h"
#include "utility.h"
//int DEBUG = 1;

int* generate_array(int max_element){
    // generate array of n elements
    static int array[TEST_NUM];
    for(int i=0; i < max_element; i++){
        array[i] = abs(rand() - rand());
    }
    return array;
}

void build_histogram(int *array, int no_of_elements, int bins){
    // display histogram
    int min, max, overall_partition_size, partition_size, idx;
    int bin_count[bins];
    int min_max[] = {(int) INFINITY,(int) -INFINITY};
    int *arr = get_min_max(array, no_of_elements, min_max);
    min = *(arr + 0);
    max = *(arr + 1);
    overall_partition_size = max - min;
    partition_size = overall_partition_size / bins;
    printf("\nmin: %d \nmax: %d\nbins: %d\npartition_size: %d\n\n", min, max, bins, partition_size);
    for(int i=0; i<bins; i++){
        write_log("%d-%d\n", min+((i)*150), min + ((i+1)*150), 3);
        bin_count[i] = 0;
    }
    for(int i=0; i<no_of_elements; i++){
        idx = (*(array + i) / partition_size);
        bin_count[idx] = bin_count[idx] + 1;
//        write_log("%d>>-%d===%d\n",i, idx, bin_count[idx]);
//        write_log("%d. %d - %d\n",i, *(array + i), (*(array + i) / partition_size));
    }
//    min_max[0] = (int) INFINITY;
//    min_max[1] = (int) -INFINITY;
//    int *res = get_min_max(bin_count, bins, min_max);
//    min = *(res + 0);
//    max = *(res + 1);

    // printing histogram
    printf("\nHISTOGRAM\n\n\n");
    for(int i=bins; i>0; i--){
//        printf("%*d\t", BAR_MARGIN, bin_count[i]);
        for(int j=0; j<bins; j++){
//            double bl = log10(bin_count[j]);
//            printf("%d.", (int) log(bin_count[j]));
            int bin_log = bin_count[j] % BAR_SCALE;
//            int bin_log = log10(bin_count[j] % BAR_SCALE);
            if(bin_log == i-1)
                printf("%*d\t", BAR_MARGIN, bin_count[j]);
            else if(bin_log >=i)
                printf("%*s\t", BAR_MARGIN, "#");
            else
                printf("%*s\t", BAR_MARGIN, " ");
        }
        printf("\n");
    }
//    printf("%*s\t", BAR_MARGIN, "values");
//    printf("%0*d\n", 20, 0);
    for(int i = 0; i < BAR_MARGIN*(bins-1)*2; i++) putchar('-');
    printf("\n");
    for(int x=0; x < bins; x++)
        printf("%*d\t", 5, min+((x)*150));
//    printf("%d\n", max);

}

//int main() {
//    printf("Initializing execution sequence...!\n");
//    int number_of_bins = BAR_SCALE;
//    build_histogram(generate_array(TEST_NUM), TEST_NUM, number_of_bins);
//    return 0;
//}

void main(){
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