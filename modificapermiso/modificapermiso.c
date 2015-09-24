#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
		if (S_ISREG(datos.st_mode)){
			mode_t permisosa = datos.st_mode; 
			//permiso de escritura a otros
			chmod(argv[1],(permisosa|S_IWOTH));
			
		}
	}
	else{
	printf("Esta mierda solo rula con archivos regulares \n");
	}

}
