#include <stdio.h>
#include <math.h>
//#include <graphics.h>
#define TEST_NUM 10000
#define BAR_SCALE 10

int* generate_array(int max_element){
    // generate array of n elements
    static int array[TEST_NUM];
    for(int i=0; i < max_element; i++){
        array[i] = rand();
    }
    return array;
}

int *get_min_max(int *array, int no_of_elements){
    int min_max[2] = {INFINITY, -INFINITY};
    // get minimum and maximum of array
    printf("elements of array: ");
    for(int i=0; i<no_of_elements; i++){
        printf("%d ", *(array + i));
        if (*(array + i) < min_max[0])
            min_max[0] = *(array + i);
        if (*(array + i) > min_max[1])
            min_max[1] = *(array + i);
    }
    return min_max;
}

void build_histogram(int *array, int no_of_elements, int bins){
    // display histogram
    int min, max, overall_partition_size, partition_size, idx;
    int *arr = get_min_max(array, no_of_elements);
    int bin_count[bins];
    min = *(arr + 0);
    max = *(arr + 1);
    overall_partition_size = max - min;
    partition_size = overall_partition_size / bins;
    printf("\nmin: %d \nmax: %d\nbins: %d\npartition_size: %d\n\n", min, max, bins, partition_size);
    for(int i=0; i<bins; i++){
        printf("%d-%d\n",min+((i)*150), min+((i+1)*150));
        bin_count[i] = 0;
    }
    for(int i=0; i<no_of_elements; i++){
        idx = (*(array + i) / partition_size);
        bin_count[idx] = bin_count[idx] + 1;
        printf("%d>>-%d===%d\n",i, idx, bin_count[idx]);
//        printf("%d. %d - %d\n",i, *(array + i), (*(array + i) / partition_size));
    }
    for(int i=0; i<bins; i++){
        printf("%d)==%d\n",i, bin_count[i] % BAR_SCALE);
    }

    printf("\nHISTOGRAM\n\n\n");
    for(int i=10; i>0; i--){
        for(int j=0; j<bins; j++){
//            printf("%d.", bin_count[j] % 10);
            if(bin_count[j] % BAR_SCALE >=i)
                printf("#\t");
            else
                printf(" \t");
        }
        printf("\n");
    }

}

int main() {
    printf("Initializing execution sequence...!\n");
//    int arr_ptr[15] = {3, 425, 324, 213, 123, 322, 455, 122, 123, 3,756,64,747,45, 55};
//    size_t arr_size = sizeof(arr_ptr);
    build_histogram(generate_array(TEST_NUM), TEST_NUM, 5);
    return 0;
}