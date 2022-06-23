/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:13:29 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/15 16:13:29 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_emulation(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!(p->info->is_died))
	{
		eat(p);
		if (p->info->all_eats)
			break ;
		print_status(p->info, p->id + 1, "is sleeping");
		usleep(p->info->time_to_sleep * 1000);
		print_status(p->info, p->id + 1, "is thinking");
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

int	main(int argc, char	**argv)
{
	t_threads		t;
	long long int	i;

	if (argc != 5 && argc != 6)
		return (0);
	if (!t_init(&t, argc, argv))
		return (0);
	i = 0;
	t.start_time = get_time();
	while (i < t.num_ph)
	{
		pthread_create(&(t.phi[i].id_thread), 0, start_emulation, &t.phi[i]);
		t.phi[i].last_eat = get_time();
		usleep(100);
		pthread_detach(t.phi->id_thread);
		i++;
	}
	start_spectator(&t);
	clean(&t);
}
