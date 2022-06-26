/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:59:13 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/26 20:31:21 by cnearing         ###   ########.fr       */
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

void	eat(t_philo	*p)
{
	int	i;
	int	j;

	if (p->info->num_ph != 1)
	{
		sem_wait(p->info->forks);
		print_status(p->info, p->id + 1, "has taken a fork");
		sem_wait(p->info->forks);
		print_status(p->info, p->id + 1, "has taken a fork");
		sem_wait(p->info->status_eat);
		print_status(p->info, p->id + 1, "is eating");
		p->last_eat = get_time();
		sem_post(p->info->status_eat);
		w_for(get_time(), p->info->time_to_eat);
		p->eat_num++;
		sem_post(p->info->forks);
		sem_post(p->info->forks);
	}
	else
	{
		sem_wait(p->info->forks);
		print_status(p->info, p->id + 1, "has taken a fork");
		sem_post(p->info->forks);
	}
}
