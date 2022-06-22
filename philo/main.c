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
//	printf("%lld №%d created\n", get_time() - p->info->start_time, p->id);
	while (!(p->info->is_died))
	{
		eat(p); // + (все что ниже новое)
		if (p->info->all_eats)
			break ;
		print_status(p->info, p->id + 1, "is sleeping");
		usleep(1000 * p->info->time_to_sleep);
		print_status(p->info, p->id + 1, "is thinking");
	}
	pthread_exit(NULL);
}

void	start_spectator(t_threads	*t) // + (new func)
{
	int	i;

	while (!(t->all_eats == t->num_eats))
	{
		i = 0;
		while ((i < t->num_ph) && !(t->is_died))
		{
			pthread_mutex_lock(&(t->status_eat));
			if (get_time() - t->phi[i].last_eat >= t->time_to_die)
			{
				print_status(t, i + 1, "died");
				t->is_died = 1;
			}
			pthread_mutex_unlock(&(t->status_eat));
			usleep(100);
		}
		if (t->is_died)
			break ;
		i = 0;
		while (t->phi[i].eat_num >= t->num_eats)
			i++;
		if (i ==  t->num_ph)
			t->all_eats = 1;
	}
}

int	main(int argc, char	**argv)
{
	t_threads		t;
	long long int	i;

	if (argc != 5 && argc != 6)
		return (0);
	if (t_init(&t, argc, argv) == 0)
		return (0);
	init_philos(&t);
	mutex_init(&t);
	i = 0;
	while (i < t.num_ph)
	{
		pthread_create(&(t.phi[i].id_thread), 0, start_emulation, &t.phi[i]);
		t.phi[i].last_eat = get_time(); // +
		pthread_detach(t.phi->id_thread);
		usleep(100);
		i++;
	}
	start_spectator(&t); // + (new line)
	clean(&t); // + (new line)
}
