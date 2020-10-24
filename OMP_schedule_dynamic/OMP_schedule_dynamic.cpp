#include <iostream>
#include <omp.h>

const int array_size = 1200000;

int main()
{
#pragma comment(linker, "/STACK:16777216")

	int first_vector[array_size], second_vector[array_size];
	for (unsigned int i = 0; i < array_size; ++i)
	{
		first_vector[i] = 1;
		second_vector[i] = 1;
	}

	omp_set_num_threads(12);

	double start_time = omp_get_wtime();

	int sum[array_size];

#pragma omp parallel shared(first_vector, second_vector, sum)
	{
#pragma omp for schedule(dynamic, 10)
		for (int i = 0; i < array_size; ++i)
		{
			sum[i] = first_vector[i] + second_vector[i];
		}
	}

	double end_time = omp_get_wtime();

	printf("\nFirst item of result = %d", sum[0]);
	printf("\nTime of work is = %f", end_time - start_time);

	return 0;
}