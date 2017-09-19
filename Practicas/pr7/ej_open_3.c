#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char** argv){
	
	//creamos un fichero con los permisos
	// rw-r--r-x
	int fd = open(argv[1], O_RDWR | O_CREAT, 0645);
	
	
	return 0;
}
