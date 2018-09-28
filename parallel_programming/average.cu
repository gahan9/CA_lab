#include <stdio.h>
# define N 500

__global__
void sum(float *array, float *sum){
    for(int i=0; i<N; i++){
        *sum += *(array + i);
    }
}

int main(){
    float *array, *summation, avg;
    float *a, summation_host = 0.0f;
    int size = sizeof(float);
    for(int i=0; i < N; i++){
        *(a + i) = i * 2.0f;
    }
    cudaMalloc(&array, N*size);
    cudaMalloc(&summation, size);

    cudaMemcpy(array, &a, N*size, cudaMemcpyHostToDevice);
    cudaMemcpy(summation, &summation_host, size, cudaMemcpyHostToDevice);

    sum<<<1, 10>>>(array, summation);

    cudaDeviceSynchronize();

    cudaMemcpy(&summation_host, summation, sizeof(float), cudaMemcpyDeviceToHost);
    avg = summation_host / N;

    cudaFree(array);
    cudaFree(summation);
    printf("avg is: %f", avg);
    return 0;
}