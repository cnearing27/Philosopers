#include "philo.h"

void	eat(t_philo	*p)
{
	pthread_mutex_lock(&(p->info->forks[p->fork_left]));
	print_status(p->info, p->id + 1, "has taken a fork");
	pthread_mutex_lock(&(p->info->forks[p->fork_right]));
	print_status(p->info, p->id + 1, "has taken a fork");
	pthread_mutex_lock(&(p->info->status_eat));
	print_status(p->info, p->id + 1, "is eating");
	p->last_eat = get_time();
	pthread_mutex_unlock(&(p->info->status_eat));
	usleep(p->info->time_to_eat * 1000); // microsec => milisec (new line)
	p->eat_num++;
	pthread_mutex_unlock(&(p->info->forks[p->fork_left]));
	pthread_mutex_unlock(&(p->info->forks[p->fork_right]));
}
