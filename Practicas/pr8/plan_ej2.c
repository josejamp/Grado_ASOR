#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

int main(){
	
	//conseguimos la politica del sistema
	int policy = sched_getscheduler(0);

	//conseguimos la prioridad del proceso
	int priority = getpriority(PRIO_PROCESS, 0);

	//conseguimos las prioridades maximas y minimas
	int max = sched_get_priority_max(policy);
	int min = sched_get_priority_min(policy);

	//las mostramos
	printf("policy: %i\n", policy);
	printf("priority: %i\n", priority);
	printf("max: %i\n", max);
	printf("min: %i\n", min);

	return 0;
}
