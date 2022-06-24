/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:13:19 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/24 13:36:55 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	semph_init(t_s	*t)
{
	int	i;

	t->status_eat = sem_open("eat", O_CREAT);
	i = -1;
	while (++i < t->num_ph)
		t->forks[i] = sem_open(ft_itoa(i), O_CREAT);
	t->writing = sem_open("wri", O_CREAT);
	return (1);
}

int	t_init(t_s	*t, int argc, char	**argv)
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
	t->forks = malloc(sizeof(sem_t) * t->num_ph);
	if (!t->forks)
		return (0);
	if (!init_philos(t))
		return (0);
	return (1);
}

int	init_philos(t_s *t)
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
		t->phi[i].last_eat = get_time();
		t->phi[i].info = t;
		i++;
	}
	if (!semph_init(t))
		return (0);
	return (1);
}
