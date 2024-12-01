#include <stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
int main() {
    int n,j=0;
    printf("enter size:");
    scanf("%d",&n);
    int** a1=(int**)malloc(n*sizeof(int));
    int** a2=(int*)malloc(n*sizeof(int));
    int** res=(int*)malloc(n*sizeof(int));
    omp_set_num_threads(8);
    #pragma omp parallel private(j)
    {
        #pragma omp for
        for(int i=0;i<n;i++){
            srand(i);
            a1[i]=(int*)malloc(n*sizeof(int));
            a2[i]=(int*)malloc(n*sizeof(int));
            res[i]=(int*)malloc(n*sizeof(int));
            for(int j=0;j<n;j++){
                a1[i][j]=rand()%100;
                a2[i][j]=rand()%100;
            }
        }
    }
    time_t st,et;
    st=clock();
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res[i][j]=0;
            for(int k=0;k<n;k++)
                res[i][j]+=a1[i][k]*a2[k][j];
            }
        }
        et=clock();
    printf("Parallel time is %lf\n",(double)(et-st)/CLOCKS_PER_SEC);
    
     st=clock();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res[i][j]=0;
            for(int k=0;k<n;k++)
                res[i][j]+=a1[i][k]*a2[k][j];
            }
        }
        et=clock();
    printf("Sequential time is %lf\n",(double)(et-st)/CLOCKS_PER_SEC);
    
    return 0;
}
