/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:13:19 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/15 17:11:56 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_threads	*t)
{
	int i;

	pthread_mutex_init(&(t->writing), NULL);
	i = 0;
	while (i < t->num_ph)
	{
		pthread_mutex_init(&(t->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(t->status_eat), NULL);
}

int	t_init(t_threads	*t, int argc, char	**argv)
{
	t->start_time = get_time();
	t->num_ph = ft_atoi(argv[1]);
	t->time_to_die = ft_atoi(argv[2]);
	t->time_to_eat = ft_atoi(argv[3]);
	t->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		t->num_eats = ft_atoi(argv[5]);
	else
		t->num_eats = -2;
	t->is_died = 0;
	if ((t->num_ph < 2 || t->time_to_die < 0 || t->time_to_eat < 0
			|| t->time_to_sleep < 0) || (argc == 6 && t->num_eats <= 0))
		return (0);
	t->phi = malloc(sizeof(t_philo) * t->num_ph);
	return (1);
}

void	init_philos(t_threads *t)
{
	int	i;

	t->phi = malloc(sizeof(t_philo) * t->num_ph);
	if (!t->phi)
		freee(t);
	t->forks = malloc(sizeof(pthread_mutex_t) * t->num_ph);
	i = 0;
	while (i < t->num_ph)
	{
		t->phi[i].id = i;
		t->phi[i].eat_num = 0;
		t->phi[i].last_eat = get_time();
		if (i != 1)
			t->phi[i].fork_left = i - 1;
		else
			t->phi[i].fork_left = t->num_ph;
		t->phi[i].fork_right = i;
		t->phi[i].info = t;
		i++;
	}
}
