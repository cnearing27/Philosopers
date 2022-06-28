/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:59:13 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/28 16:21:33 by cnearing         ###   ########.fr       */
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
	if (p->info->num_ph != 1)
	{
		sem_wait(p->info->status_eat);
		sem_wait(p->info->forks);
		print_status(p->info, p->id + 1, "has taken a fork");
		sem_wait(p->info->forks);
		print_status(p->info, p->id + 1, "has taken a fork");
		sem_post(p->info->status_eat);
		print_status(p->info, p->id + 1, "is eating");
		p->last_eat = get_time();
		p->eat_num++;
		w_for(get_time(), p->info->time_to_eat);
		sem_post(p->info->forks);
		sem_post(p->info->forks);
		if (p->eat_num == p->info->num_eats)
			exit(5);
	}
	else
	{
		sem_wait(p->info->forks);
		print_status(p->info, p->id + 1, "has taken a fork");
	}
}
