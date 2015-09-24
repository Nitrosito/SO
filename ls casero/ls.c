
#include <sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>		//Needed for open
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h> // Necesaria para opendir



int main(int argc, char *argv[])
{
	if (argc != 2) { // Si no tiene 2 argumentos
		printf ("Por favor, introduce 2 argumentos (Ruta)\n");
		exit(EXIT_FAILURE); // Salgo informando de salida erronea
	}

	// VARIABLES
	 DIR *dirp;
	 struct dirent *direntp;

	 struct stat atributos;

	 
	 // Abrimos el directorio //
	 dirp = opendir(argv[1]);
	 if (dirp == NULL){
		 printf("Error: No se puede abrir el directorio\n");
		 exit(EXIT_FAILURE);
	 }
	 
	 chdir(argv[1]) ; // NOS MOVEMOS DE DIRECTORIO! CUANDO QUEBRADERO DE CABEZA CON ESTO!

	 // Leemos las entradas del directorio //
	 while ((direntp = readdir(dirp)) != NULL) {

	 	
	if(stat(direntp->d_name,&atributos) < 0) {
	  printf("\nError al intentar acceder a los atributos de %s \n",direntp->d_name);
	  //exit(-1);
	}
	
	else{
	    printf( (S_ISDIR(atributos.st_mode)) ? "d" : "-" );
	    printf( (atributos.st_mode & S_IRUSR) ? "r" : "-");
	    printf( (atributos.st_mode & S_IWUSR) ? "w" : "-");
	    printf( (atributos.st_mode & S_IXUSR) ? "x" : "-");
	    printf( (atributos.st_mode & S_IRGRP) ? "r" : "-");
	    printf( (atributos.st_mode & S_IWGRP) ? "w" : "-");
	    printf( (atributos.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (atributos.st_mode & S_IROTH) ? "r" : "-");
	    printf( (atributos.st_mode & S_IWOTH) ? "w" : "-");
	    printf( (atributos.st_mode & S_IXOTH) ? "x" : "-");
	   	printf("\t\t %s    ",direntp->d_name) ;
	    printf("\n");
	}
	
 }
	 

	 closedir(dirp); 	 // Cerramos el directorio //


}