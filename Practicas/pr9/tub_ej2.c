#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
	
	int fd = open("tuberia", O_WRONLY);

	write(fd, argv[1], sizeof(argv[1]));

	close(fd);
	
	return 0;
}
