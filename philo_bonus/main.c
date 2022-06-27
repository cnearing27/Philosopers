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

void	start_emulation(t_philo	*p)
{
	p->last_eat = get_time();
	pthread_create(&p->id_thread, NULL, start_spectator, p);
	pthread_detach(p->id_thread);
	while (p->info->is_died == 0)
	{
		eat(p);
		if (p->eat_num >= p->info->num_eats && p->info->num_eats != -2)
			break ;
		print_status(p->info, p->id + 1, "is sleeping");
		w_for(get_time(), p->info->time_to_sleep);
		print_status(p->info, p->id + 1, "is thinking");
	}
	usleep(100);
}

void	*start_spectator(void	*arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!(p->info->is_died))
	{
		sem_wait(p->info->status_eat);
		if ((get_time() - p->last_eat) > p->info->time_to_die)
		{
			print_status(p->info, (p->id) + 1, "died");
			sem_wait(p->info->writing);
			p->info->is_died = 1;
			exit (4);
		}
		sem_post(p->info->status_eat);
	}
	return (NULL);
}

int	main(int argc, char	**argv)
{
	t_s				t;
	long long int	i;

	if (argc != 5 && argc != 6)
		return (0);
	if (!t_init(&t, argc, argv))
		return (0);
	i = 0;
	t.start_time = get_time();
	while (i < t.num_ph)
	{
		t.phi[i].id_proc = fork();
		if (t.phi[i].id_proc < 0)
			return (0);
		if (t.phi[i].id_proc == 0)
			start_emulation(&t.phi[i]);
		i++;
	}
	clean(&t);
}
