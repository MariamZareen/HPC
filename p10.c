//p10.c
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

void main(){
	int n;
	
	printf("Enter dimension of square matrices: ");
	scanf("%d",&n);
	
	time_t st,et;
	st=clock();
	
	int **a1=(int **) malloc (n*sizeof(int *));
	int **a2=(int **) malloc (n*sizeof(int *));
	int **res=(int **) malloc (n*sizeof(int *));
	
	int i=0,j=0,k=0;
	
	omp_set_num_threads(omp_get_max_threads());
	
	#pragma omp parallel private(j)
	{
		#pragma omp for
		for(i=0;i<n;i++){
			srand(i);
			
			a1[i]=(int *) malloc (n*sizeof(int));
			a2[i]=(int *) malloc (n*sizeof(int));
			res[i]=(int *) malloc (n*sizeof(int));
			for(j=0;j<n;j++){
				a1[i][j]=rand()%100;
				a2[i][j]=rand()%100;
			}			
		}		
	}
	#pragma omp parallel private(j,k)
	{
		#pragma omp for
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				res[i][j]=0;
				for(k=0;k<n;k++)
					res[i][j]+=a1[i][k]*a2[k][j];
			}			
		}
	}	
	
	et=clock();
	double t1=(double)(et-st)/CLOCKS_PER_SEC;
	printf("\nTime Taken by parallel algorithm: %f",t1);
	
	st=clock();	
	for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				res[i][j]=0;
				for(k=0;k<n;k++)
					res[i][j]+=a1[i][k]*a2[k][j];
			}			
		}
	et=clock();
	double t2=(double)(et-st)/CLOCKS_PER_SEC;
	printf("\nTime Taken by sequential algorithm: %f\n",t2);
	
	
	
}
