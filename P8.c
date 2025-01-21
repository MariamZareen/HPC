//pg8
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define SIZE 6
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int main(int argc,char* argv[]){
	int rank,size,src,dest;
	int inbuf[4]={MPI_PROC_NULL, MPI_PROC_NULL, MPI_PROC_NULL, MPI_PROC_NULL, };
	int outbuf;
	int nbrs[4];
	int dims[2]={3,2};
	int periods[2]={0,0};
	int reorder=0;
	int coords[2];
	
	MPI_Request reqs[8];
	MPI_Status stats[8];
	MPI_Comm cartcomm;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(size==SIZE){
		MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
		MPI_Comm_rank(cartcomm,&rank);
		MPI_Cart_coords(cartcomm,rank,2,coords);
		MPI_Cart_shift(cartcomm, 0, 1, &nbrs[UP], &nbrs[DOWN]);
		MPI_Cart_shift(cartcomm, 1, 1, &nbrs[LEFT], &nbrs[RIGHT]);
		printf("rank= %d coords %d %d neighbours(u,d,l,r): %d %d %d %d\n",rank,coords[0],coords[1],nbrs[UP],nbrs[DOWN],nbrs[LEFT],nbrs[RIGHT]);
		outbuf=rank;
		for(int i=0;i<4;i++){
			dest=nbrs[i];
			src=nbrs[i];
			MPI_Isend(&outbuf,1,MPI_INT,dest,1,MPI_COMM_WORLD,&reqs[i]);
			MPI_Irecv(&inbuf[i],1,MPI_INT,src,1,MPI_COMM_WORLD,&reqs[i+4]);
		}
		MPI_Waitall(8,reqs,stats);
		printf("rank= %d coords %d %d inbuf(u,d,l,r): %d %d %d 	%d\n",rank,coords[0],coords[1],inbuf[UP],inbuf[DOWN],inbuf[LEFT],inbuf[RIGHT]);
	}else
		printf("\nMust specify %d tasks. Termination\n",SIZE);
	MPI_Finalize();
	return 0;
}
