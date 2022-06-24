/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:59:13 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/24 13:43:22 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	w_for(unsigned long long w_start, unsigned long long w_f)
{
	while (1)
	{
		if ((get_time() - w_start) >= w_f)
			break ;
		usleep(50);
	}
}

int	find_fork(t_s	*t)
{
	
}

void	eat(t_philo	*p)
{
	int	i;
	int	j;
	
	if (p->info->num_ph != 1)
	{
		i = find_fork(p->info);
		sem_wait(p->info->forks[i]);
		print_status(p->info, p->id + 1, "has taken a fork");
		j = find_fork(p->info);
		sem_wait(p->info->forks[j]);
		print_status(p->info, p->id + 1, "has taken a fork");
		sem_wait(p->info->status_eat);
		print_status(p->info, p->id + 1, "is eating");
		p->last_eat = get_time();
		sem_post(p->info->status_eat);
		w_for(get_time(), p->info->time_to_eat);
		p->eat_num++;
		sem_post(p->info->forks[i]);
		sem_post(p->info->forks[j]);
	}
	else
	{
		sem_wait(p->info->forks[0]);
		print_status(p->info, p->id + 1, "has taken a fork");
		sem_post(p->info->forks[0]);
	}
}
