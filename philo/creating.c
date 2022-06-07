#include "philo.h"

int	t_init(my_threads	*t)
{
	t->start_time = get_time();
	t->threads = malloc(sizeof(pthread_t) * t->num_ph);
	if (!t->threads)
		return (0);
	t->status = malloc(sizeof(int) * t->num_ph);
	if (!t->status)
	{
		freee(t);
		return (0);
	}
	t->status_addr = malloc(sizeof(int) * t->num_ph);
	if (!t->status_addr)
	{
		freee(t);
		return (0);
	}
	return (1);
}

void	init_philos(my_threads	*t)
{
	int	i;

	t->phil = malloc(sizeof(philo));
	if (!t->phil)
		freee(t);
	i = 1;
	while (i <= t->num_ph)
	{
		t->phil[i].id = i;
		t->phil[i].eat_num = 0;
		t->phil[i].last_eat = 0;
		if (i != 1)
			t->phil[i].fork_left = i - 1;
		else
			t->phil[i].fork_left = t->num_ph;
		t->phil[i].fork_right = i;
		i++;
	}
}

