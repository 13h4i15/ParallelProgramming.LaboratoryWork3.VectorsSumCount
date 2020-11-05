#include <cstdio>
#include <cstdlib>
#include <omp.h>

const int array_size = 1200000;

int main()
{
	int* first_vector, * second_vector;
	first_vector = (int*)malloc(array_size * sizeof(int));
	second_vector = (int*)malloc(array_size * sizeof(int));
	int i;
	for (i = 0; i < array_size; ++i)
	{
		first_vector[i] = 1;
		second_vector[i] = 1;
	}

	omp_set_num_threads(12);

	double start_time, end_time;
	start_time = omp_get_wtime();

	int* sum;
	sum = (int*)malloc(array_size * sizeof(int));

#pragma omp parallel shared(first_vector, second_vector, sum)
	{
#pragma omp for schedule(dynamic, 10)
		for (i = 0; i < array_size; ++i)
		{
			sum[i] = first_vector[i] + second_vector[i];
		}
	}

	end_time = omp_get_wtime();

	printf("\nFirst item of result = %d", sum[0]);
	printf("\nTime of work is = %f", end_time - start_time);

	return 0;
}