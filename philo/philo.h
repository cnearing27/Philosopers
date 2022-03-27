#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <string.h> //memset
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

typedef struct s_threads
{
	pthread_t		*threads;
	int				*status;
	int				*status_addr;
	long long int	num;
}	my_threads;

long long int	ft_atoi(const char	*str);
int				t_init(my_threads	*t);
void			freee(my_threads	*t);

# endif
