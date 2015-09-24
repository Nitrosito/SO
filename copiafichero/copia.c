#include<stdio.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){

	int fd,fd1,efd1,r1;
	char leidofd[512];

	fd = open("entrada.txt",O_RDONLY);	
	if (fd < 0){
		perror("Error en el open");
		exit(1);
	}

	fd1 = open("salida.txt",O_CREAT|O_WRONLY,S_IRWXU);
	if (fd1 < 0){
		perror("Error en el open");
		exit(1);
	}

	while (	(r1 = read (fd,leidofd, 512)) > 0){
	
		efd1 = write(fd1,&leidofd,r1);
		if (efd1 < 0 ){
			perror("Error en el write");
			exit(1);
		}
	}

	close(fd);
	close(fd1);

	
}












