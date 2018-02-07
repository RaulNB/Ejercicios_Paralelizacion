#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM 10000
#define NUM_THREADS 2

void* aumentar_valor (void *x) {
 	int *count = (int *)malloc(sizeof(int));
 	*count = 0;
 	for (int i = 0; i < TAM; ++i) {
 		(*count)++;
 	}
 	pthread_exit((void *)count);
 }

int main(int argc, char const *argv[])
{
	int suma = 0;
	void *stat;

	pthread_t threads[NUM_THREADS];

	for (int t = 0; t < NUM_THREADS; t++) {
		pthread_create(&threads[t], NULL, aumentar_valor, NULL);
	}

	for (int t = 0; t < NUM_THREADS; t++) {
		pthread_join(threads[t], &stat);
		suma = suma + *(int *)stat;
		free(stat);
	}

	printf("%d\n", suma);

	pthread_exit(NULL);
}