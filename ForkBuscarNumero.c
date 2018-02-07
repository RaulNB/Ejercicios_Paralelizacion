#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int Tam = 1000;
int n = 5;
int numBuscar = 900;

int main() {
	int stat;
	int valor = -1;
	int num_encontrado = 0;
	int* array = NULL;
	
	array=(int *)malloc(Tam*sizeof(int));

	for (int i = 0; i < Tam; i++) {
		array[i] = i;
	}

	int x = 1;
	for (int i = 0; i < Tam; i++) {
		if (x != 0) {
			x = fork();
		}
		if (x == 0 && valor == -1) {
			valor = i;
		}
	} 

	if (x == 0) {
		for (int i = valor * (Tam/n); i < ((valor + 1) * (Tam/n) - 1); i++) {
			if (array [i] == numBuscar) {
				exit (valor + 1);
			}
		}
		exit (0);
	}

	for (int i = 0; i < n; i++) {
		wait (&stat);
		if (WEXITSTATUS(stat) != 0) {
			printf("Hijo %d lo ha encontrado\n", WEXITSTATUS(stat));
		}
	}

	free (array);

	return 0;
}