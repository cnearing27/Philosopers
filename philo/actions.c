/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:59:13 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/28 15:37:09 by cnearing         ###   ########.fr       */
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
	pthread_mutex_lock(&(p->info->writing));
	if (p->info->num_ph != 1)
	{
		pthread_mutex_unlock(&(p->info->writing));
		pthread_mutex_lock(&(p->info->forks[p->fork_left]));
		print_status(p->info, p->id + 1, "has taken a fork");
		pthread_mutex_lock(&(p->info->forks[p->fork_right]));
		print_status(p->info, p->id + 1, "has taken a fork");
		print_status(p->info, p->id + 1, "is eating");
		pthread_mutex_lock(&(p->info->writing));
		p->last_eat = get_time();
		p->eat_num++;
		if (p->eat_num == p->info->num_eats)
			p->info->all_eats++;
		pthread_mutex_unlock(&(p->info->writing));
		w_for(get_time(), p->info->time_to_eat);
		pthread_mutex_unlock(&(p->info->forks[p->fork_left]));
		pthread_mutex_unlock(&(p->info->forks[p->fork_right]));
	}
	else
	{
		pthread_mutex_unlock(&(p->info->writing));
		pthread_mutex_lock(&(p->info->forks[p->fork_right]));
		print_status(p->info, p->id + 1, "has taken a fork");
	}
}

void	*start_emulation(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!(p->info->is_died))
	{
		eat(p);
		if (p->info->num_ph != 1)
		{
			print_status(p->info, p->id + 1, "is sleeping");
			w_for(get_time(), p->info->time_to_sleep);
			print_status(p->info, p->id + 1, "is thinking");
		}
	}
	return (NULL);
}

void	start_spectator(t_threads	*t)
{
	int	i;

	while (1)
	{
		i = 0;
		while ((i < t->num_ph))
		{
			pthread_mutex_lock(&(t->writing));
			if (t->all_eats >= t->num_ph)
				return ;
			if ((get_time() - t->phi[i].last_eat) >= t->time_to_die)
			{
				pthread_mutex_unlock(&(t->writing));
				print_status(t, i + 1, "died");
				pthread_mutex_lock(&(t->writing));
				t->is_died = 1;
				return ;
			}
			pthread_mutex_unlock(&(t->writing));
			i++;
		}
	}
}
