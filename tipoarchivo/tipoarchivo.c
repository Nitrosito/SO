#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
	if (argc < 2){
		perror("Por favor, introduce solo 1 argumento\n");
		exit(1);
	}
	
	struct stat datos;

	if( (stat(argv[1],&datos)) < 0 ){
		perror("No se pudieron acceder a los datos del archivo\n");
		exit(1);
	}
	
	
	if (S_ISREG(datos.st_mode)){
		printf("Es un archivo regular\n");
		exit(1);
	}
	
	if (S_ISDIR(datos.st_mode)){
		printf("Es un directorio\n");
		exit(1);
	}

	printf("No tengo ni puta idea, de que coño es\n");
	

}
