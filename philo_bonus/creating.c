/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:13:19 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/28 16:17:15 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	semph_init(t_s	*t)
{
	sem_unlink("/forks");
	sem_unlink("/eat");
	sem_unlink("/write");
	t->status_eat = sem_open("/eat", O_CREAT, S_IRWXU, 1);
	if (t->status_eat == SEM_FAILED)
		return (0);
	t->forks = sem_open("/forks", O_CREAT, S_IRWXU, t->num_ph);
	if (t->forks == SEM_FAILED)
		return (0);
	t->writing = sem_open("/write", O_CREAT, S_IRWXU, 1);
	if (t->writing == SEM_FAILED)
		return (0);
	if (!init_philos(t))
		return (0);
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
	if ((t->num_ph < 1 || t->time_to_die <= 0 || t->time_to_eat <= 0
			|| t->time_to_sleep <= 0) || (argc == 6 && t->num_eats <= 0))
	{
		printf("wrong arguments!\n");
		return (0);
	}
	if (!semph_init(t))
		return (0);
	return (1);
}

int	init_philos(t_s *t)
{
	int	i;

	i = 0;
	while (i < t->num_ph)
	{
		t->phi[i].id = i;
		t->phi[i].eat_num = 0;
		t->phi[i].last_eat = 0;
		t->phi[i].info = t;
		i++;
	}
	return (1);
}
