#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Por favor introduce el nombre del fifo");
		exit(1);
	}
	int fd;
	if ( (fd = open(argv[1],O_WRONLY)) < 0){
		perror("Error abriendo el archivo fifo");
		exit(1);
	}
	
	while(1==1){
		int dato;
		char cadena[1];
		scanf("%s",cadena);
		sscanf(cadena,"%d",&dato);

		if(dato==0){
		write(fd,&dato, sizeof(int));
		exit(0);
		}

		else{
			write(fd,&dato, sizeof(int));
		}
	}
}

