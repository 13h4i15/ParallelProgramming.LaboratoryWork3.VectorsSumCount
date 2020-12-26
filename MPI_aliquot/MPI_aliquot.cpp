#include <cstdio>
#include <cstdlib>
#include "mpi.h"

const int array_size = 600000;

int main(int argc, char* argv[])
{
	int proc_rank, proc_size;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &proc_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
	int *first_vector, *second_vector;
	first_vector = (int*)malloc(array_size * sizeof(int));
	second_vector = (int*)malloc(array_size * sizeof(int));
	int i;
	if (proc_rank == 0)
	{
		for (i = 0; i < array_size; ++i)
		{
			first_vector[i] = 1;
			second_vector[i] = 1;
		}
	}
	int local_size;
	local_size = array_size / proc_size;
	int *first_local_vector, *second_local_vector;
	first_local_vector = (int*)malloc(local_size * sizeof(int));
	second_local_vector = (int*)malloc(local_size * sizeof(int));

	MPI_Scatter(first_vector, local_size, MPI_INT, first_local_vector, local_size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(second_vector, local_size, MPI_INT, second_local_vector, local_size, MPI_INT, 0, MPI_COMM_WORLD);
	double start_time, end_time;
	start_time = MPI_Wtime();

	int* sum_local;
	sum_local = (int*)malloc(local_size * sizeof(int));
	for (i = 0; i < local_size; ++i)
	{
		sum_local[i] = first_local_vector[i] + second_local_vector[i];
	}
	end_time = MPI_Wtime();

	int* sum;
	sum = (int*)malloc(array_size * sizeof(int));
	MPI_Gather(sum_local, local_size, MPI_INT, sum, local_size, MPI_INT, 0, MPI_COMM_WORLD);

	if (proc_rank == 0)
	{
		printf("\nFirst item of result = %d", sum[0]);
		printf("\nTime of work is = %f", end_time - start_time);
	}
	MPI_Finalize();

	free(first_vector);
	free(second_vector);
	free(second_local_vector);
	free(sum_local);
	free(sum);

	return 0;
}
