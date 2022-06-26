/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:13:19 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/26 20:27:43 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_threads	*t)
{
	int	i;

	if (pthread_mutex_init(&(t->writing), NULL))
		return (0);
	i = -1;
	while (++i < t->num_ph)
	{
		if (pthread_mutex_init(&(t->forks[i]), NULL))
			return (0);
	}
	if (pthread_mutex_init(&(t->status_eat), NULL))
		return (0);
	return (1);
}

int	t_init(t_threads	*t, int argc, char	**argv)
{
	t->num_ph = ft_atoi(argv[1]);
	t->time_to_die = ft_atoi(argv[2]);
	t->time_to_eat = ft_atoi(argv[3]);
	t->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		t->num_eats = ft_atoi(argv[5]);
	else
		t->num_eats = -2;
	t->is_died = 0;
	if ((t->num_ph < 1 || t->time_to_die < 0 || t->time_to_eat < 0
			|| t->time_to_sleep < 0) || (argc == 6 && t->num_eats <= 0))
	{
		printf("wrong arguments!\n");
		return (0);
	}
	t->all_eats = 0;
	t->forks = malloc(sizeof(pthread_mutex_t) * t->num_ph);
	if (!t->forks)
		return (0);
	if (!init_philos(t))
		return (0);
	return (1);
}

int	init_philos(t_threads *t)
{
	int	i;

	t->phi = malloc(sizeof(t_philo) * t->num_ph);
	if (!t->phi)
		return (0);
	i = 0;
	while (i < t->num_ph)
	{
		t->phi[i].id = i;
		t->phi[i].eat_num = 0;
		t->phi[i].last_eat = 0; // ()gettimme
		if (i != 0)
			t->phi[i].fork_left = i - 1;
		else
			t->phi[i].fork_left = t->num_ph;
		t->phi[i].fork_right = i;
		t->phi[i].info = t;
		i++;
	}
	if (!mutex_init(t))
		return (0);
	return (1);
}
