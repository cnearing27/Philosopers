/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:59:13 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/27 14:38:36 by cnearing         ###   ########.fr       */
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
		pthread_mutex_lock(&(p->info->forks[p->fork_left]));
		print_status(p->info, p->id + 1, "has taken a fork");
		pthread_mutex_lock(&(p->info->forks[p->fork_right]));
		print_status(p->info, p->id + 1, "has taken a fork");
		pthread_mutex_lock(&(p->info->status_eat));
		print_status(p->info, p->id + 1, "is eating");
		p->last_eat = get_time();
		p->eat_num++;
		pthread_mutex_unlock(&(p->info->status_eat));
		w_for(get_time(), p->info->time_to_eat);
		pthread_mutex_unlock(&(p->info->forks[p->fork_left]));
		pthread_mutex_unlock(&(p->info->forks[p->fork_right]));
	}
	else
	{
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
			if (p->info->all_eats)
				break ;
			print_status(p->info, p->id + 1, "is sleeping");
			w_for(get_time(), p->info->time_to_sleep);
			print_status(p->info, p->id + 1, "is thinking");
		}
	}
	pthread_exit(NULL);
}

void	start_spectator(t_threads	*t)
{
	int	i;

	while (!(t->all_eats == 1))
	{
		i = 0;
		while ((i < t->num_ph) && !(t->is_died))
		{
			pthread_mutex_lock(&(t->status_eat));
			if ((get_time() - t->phi[i].last_eat) >= t->time_to_die)
			{
				print_status(t, i + 1, "died");
				t->is_died = 1;
			}
			pthread_mutex_unlock(&(t->status_eat));
			i++;
			usleep(100);
		}
		if (t->is_died)
			break ;
		i = 0;
		while (t->phi[i].eat_num >= t->num_eats && t->num_eats != -2)
			i++;
		if (i == t->num_ph)
			t->all_eats = 1;
	}
}
