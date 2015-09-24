#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

void  opcion1(const char* ruta){
	DIR* directorio;
	struct dirent * entrada;
	struct stat attr;
	char nombre_fichero[256];
	if((directorio = opendir(ruta)) == NULL){
	perror ("Directorio");
	exit(1);
	}
	
	while ( (entrada=readdir(directorio)) != NULL){
		
		sprintf(nombre_fichero,"%s/%s",ruta,entrada->d_name);
		if ((stat(nombre_fichero,&attr)) < 0){
			perror("Error en stat");
		}

		if(S_ISREG(attr.st_mode)){
			int peso = attr.st_size;
			printf(" %s   tamaño: %d Bytes %d KB \n", entrada->d_name, peso,peso/1024);
		}

	}
	closedir(directorio);
}

void opcion2(const char* ruta){
	DIR* directorio;
	struct dirent * entrada;
	struct stat attr;
	char nombre_fichero[256];
	if((directorio = opendir(ruta)) == NULL){
	perror ("Directorio");
	exit(1);
	}
	
	while ( (entrada=readdir(directorio)) != NULL){
		
		sprintf(nombre_fichero,"%s/%s",ruta,entrada->d_name);
		if ((stat(nombre_fichero,&attr)) < 0){
			perror("Error en stat");
		}

		if(S_ISDIR(attr.st_mode)){
			      // IMPRIMIENDO PERMISOS//
			  printf( (attr.st_mode & S_IRUSR) ? "r" : "-");
			  printf( (attr.st_mode & S_IWUSR) ? "w" : "-");
			  printf( (attr.st_mode & S_IXUSR) ? "x" : "-");
			  printf( (attr.st_mode & S_IRGRP) ? "r" : "-");
			  printf( (attr.st_mode & S_IWGRP) ? "w" : "-");
			  printf( (attr.st_mode & S_IXGRP) ? "x" : "-");
			  printf( (attr.st_mode & S_IROTH) ? "r" : "-");
			  printf( (attr.st_mode & S_IWOTH) ? "w" : "-");
			  printf( (attr.st_mode & S_IXOTH) ? "x" : "-");
			  printf(" %s", entrada->d_name);
		 	  printf("\n");
			 }	
		}

	closedir(directorio);
}

int  opcion3(const char* ruta){
	DIR* directorio;
	struct dirent * entrada;
	struct stat attr;
	char nombre_fichero[256];
	if((directorio = opendir(ruta)) == NULL){
	perror ("Directorio");
	exit(1);
	}
	
	while ( (entrada=readdir(directorio)) != NULL){
		sprintf(nombre_fichero,"%s/%s",ruta,entrada->d_name);
		if ((stat(nombre_fichero,&attr)) < 0){
			perror("Error en stat primero");
		}

		if(S_ISREG(attr.st_mode)){
			  // AHORA TENGO QUE CAMBIARLE LOS PERMISOS!
			  mode_t permisosa = attr.st_mode; // GUARDO LOS PERMISOS QUE TENIA ANTES 
			//permiso de lectura escritura y ejecucion para otros mas los que tenia antes
			  if(chmod(nombre_fichero,(permisosa | S_IRWXO))  < 0) {
			 	 perror("\nError en chmod");
			  	 exit(1);
			  }

			  
			} // Cierre si es archivo
		} // cierre mientras lea archivos
		return 1;
		closedir(directorio);
	}

int main(int argc, char* argv[]){
	 if(argc != 3){
	 	printf("Error de argumentos ( [RUTA A EXPLORAR] [NOMBREFIFO]) \n");
	    	exit(1);
	 }	
	
	// Creo el archivo fifo dado como argumento en la ejecución del programa
	mkfifo(argv[2], 0777);
	int fd = open(argv[2],O_RDONLY);
	int dato;
	
	while(1==1){
		//Leo dato del fifo
		read(fd, &dato, sizeof(int));
		if(dato==0){
			printf("\n Eligio finalizar el programa\n");
			exit(0); 
		}
	
		if(dato==1){
		  	opcion1(argv[1]);
		}

		if(dato==2){
			opcion2(argv[1]);
		}
	
		if(dato==3){
			if( (opcion3(argv[1]) == 1)){
				printf("\nPermisos modificados con exito\n");
			}
		}

	}
}

 
