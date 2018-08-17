#include <stdio.h>
#include <math.h>
#include <stdarg.h>
//#include <graphics.h>
#define TEST_NUM 10000
#define BAR_SCALE 10
#define BAR_MARGIN 5
#define DEBUG 0

int write_log(const char *format, ...)
{
    if(DEBUG) {
        va_list args;
        va_start (args, format);
        vprintf(format, args);
        va_end (args);
    }
}

int* generate_array(int max_element){
    // generate array of n elements
    static int array[TEST_NUM];
    for(int i=0; i < max_element; i++){
        array[i] = rand() % 1000;
    }
    return array;
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

void build_histogram(int *array, int no_of_elements, int bins){
    // display histogram
    int min, max, overall_partition_size, partition_size, idx;
    int min_max[2] = {INFINITY, -INFINITY};
    int *arr = get_min_max(array, no_of_elements, min_max);
    int bin_count[bins], bin_range;
    min = *(arr + 0);
    max = *(arr + 1);
    overall_partition_size = max - min;
    partition_size = overall_partition_size / bins;
    printf("\nmin: %d \nmax: %d\nbins: %d\npartition_size: %d\n\n", min, max, bins, partition_size);
    for(int i=0; i<bins; i++){
        write_log("%d-%d\n", min+((i)*150), min + ((i+1)*150));
        bin_count[i] = 0;
    }
    for(int i=0; i<no_of_elements; i++){
        idx = (*(array + i) / partition_size);
        bin_count[idx] = bin_count[idx] + 1;
//        write_log("%d>>-%d===%d\n",i, idx, bin_count[idx]);
//        write_log("%d. %d - %d\n",i, *(array + i), (*(array + i) / partition_size));
    }
    printf("\nHISTOGRAM\n\n\n");
    for(int i=bins; i>0; i--){
//        printf("%*d\t", BAR_MARGIN, bin_count[i]);
        for(int j=0; j<bins; j++){
//            double bl = log10(bin_count[j]);
//            printf("%d.", (int) log(bin_count[j]));
            int bin_log = bin_count[j] % BAR_SCALE;
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

}

int main() {
    printf("Initializing execution sequence...!\n");
    int number_of_bins = 10;
    build_histogram(generate_array(TEST_NUM), TEST_NUM, number_of_bins);
    return 0;
}