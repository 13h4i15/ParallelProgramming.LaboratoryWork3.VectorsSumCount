#include <iostream>
#include "mpi.h"

const int array_size = 1200000;

int main(int argc, char* argv[])
{
#pragma comment(linker, "/STACK:12777216")

	int proc_rank, proc_size;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &proc_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

	int first_vector[array_size], second_vector[array_size];
	if (proc_rank == 0)
	{
		for (unsigned int i = 0; i < array_size; ++i)
		{
			first_vector[i] = 1;
			second_vector[i] = 1;
		}
	}
}
