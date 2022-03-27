#include "philo.h"

void* helloWorld(void *args) {
    printf("Hello from thread!\n");
	return 0;
}

int main()
{
	pthread_t	t1;
	int			status;
	int			status_addr;

	status = pthread_create(&t1, NULL, helloWorld, NULL);
	status = pthread_join(t1, (void**)&status_addr);
}
