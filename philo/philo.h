#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <string.h> //memset
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

typedef struct philosophers
{
	int	id;
	int	eat_num;
	int	fork_left;
	int	fork_right;
	int	last_eat;
}	philo;

typedef struct s_threads
{
	pthread_t		*threads;
	int				*status;
	int				*status_addr;
	long long		start_time;
	long long int	num_ph;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	num_eats;
	pthread_mutex_t	*forks;
	philo			*phil;
}	my_threads;

long long int	ft_atoi(const char	*str);
int				t_init(my_threads	*t);
void			freee(my_threads	*t);
void			*new_philo(void	*args);
int				check_info(my_threads t, int argc);
void			init_philos(my_threads	*t);
long long		get_time(void);

# endif
