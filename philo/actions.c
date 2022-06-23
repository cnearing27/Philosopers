/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:59:13 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/23 15:15:30 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	usleep(p->info->time_to_eat * 1000);
	p->eat_num++;
	pthread_mutex_unlock(&(p->info->forks[p->fork_left]));
	pthread_mutex_unlock(&(p->info->forks[p->fork_right]));
}
