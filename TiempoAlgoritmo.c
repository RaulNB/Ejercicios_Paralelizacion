#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 400000000 //Número de posiciones del array

int main(int argc, char const *argv[])
{
	//Colocar la semilla del tiempo a NULL
	srand(time(NULL));

	//Establecer número de hilos para paralelizar
	omp_set_num_threads(4);

	//Creación de arrays v1 y v2 dinamicos con valores aleatorios entre 0 y 999
	double *v1;
	double *v2;

	v1 = (double *)malloc(N*sizeof(double));
	v2 = (double *)malloc(N*sizeof(double));

	for (int i = 0; i < N; ++i)
	{
		v1[i] = rand()%1000;
		v2[i] = rand()%1000;
	}

	//Declaración de variables
	double mayor = 0;
	double mayorV1 = 0;
	double mayorV2 = 0;

	//Algoritmo
	double inicio = omp_get_wtime();

	#pragma omp parallel reduction (max:mayorV1, mayorV2)
	{
		printf("%d\n",omp_get_num_threads());
		mayorV1 = v1[0];
		mayorV2 = v2[0];

		#pragma omp for
		for (int i = 1; i < N; ++i)
		{
			if(v1[i] > mayorV1)
			{
				mayorV1 = v1[i];
			}
			if(v2[i] > mayorV2)
			{
				mayorV2 = v2[i];
			}
		}
	}

	mayor = abs(mayorV1 * mayorV2);
	
	double fin = omp_get_wtime();

	//Mostrar resultados
	printf("El mayor es %lf\n", mayor);
	printf("El tiempo de ejecución es %lf\n", fin - inicio);

	//Liberar memoria
	free(v1);
	free(v2);

	return 0;
}