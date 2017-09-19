#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	
	/***************************************
		YA COMENTADO EN PID_EJ3.C
	
	**************************************/
	
	pid_t hijo, grupo, sesion;

	struct rlimit rlim;

	hijo = getpid();
	grupo = getpgid(0);
	sesion = getsid(0);

	int archivos = getrlimit(RLIMIT_NOFILE, &rlim);
	
	char* buff;
	char buff2[80];
	
	buff = getcwd(buff2, 80);
	
	printf("pid: %i\n", hijo);
	printf("pgid: %i\n", grupo);
	printf("sesion: %i\n", sesion);
	printf("archivos: %i\n", rlim.rlim_max);
	printf("path: %s\n", buff);

	
	
	return 0;
}
