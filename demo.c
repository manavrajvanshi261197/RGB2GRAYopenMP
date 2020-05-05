#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include<time.h>

int i,j,k;
int w,h;

FILE *fpTime; 

int main(){
    fpTime = fopen("timeParallelDynamic.txt", "w");
    srand(time(0)); 
    int size = 100;
    for(size = 100; size < 2000; size++){
        w = size;
        h = size;
        float (*R)[h] = malloc(sizeof(float[w][h])); 
        float (*G)[h] = malloc(sizeof(float[w][h])); 
        float (*B)[h] = malloc(sizeof(float[w][h])); 
        float (*BW)[h] = malloc(sizeof(float[w][h])); 
        for( i = 0; i < w; i++ ){
            for( j = 0; j < h; j++ ){
                R[i][j] = rand()%256;
                G[i][j] = rand()%256;
                B[i][j] = rand()%256;
            }
        }
        // printf("Staring Converting\n");
        double start_time = omp_get_wtime();
        // #pragma omp parallel for 
        #pragma omp parallel for collapse(2) schedule (static)
        for( i = 0; i < w; i++ ){
            for( j = 0; j < h; j++ ){
                BW[i][j] = R[i][j] * 0.299 ;
                BW[i][j] += G[i][j] * 0.587 ;
                BW[i][j] += B[i][j] * 0.114 ;
            }
        }
        double time = omp_get_wtime() - start_time;
        fprintf(fpTime, "%f\n", time);
        printf("Size = %d\n", size);
        // printf("BW random = %f\n", BW[34][54]);
        printf("Time Taken : %f\n\n", time);
        free(R);
        free(G);
        free(B);
        free(BW);

    }
    fclose(fpTime);
}

