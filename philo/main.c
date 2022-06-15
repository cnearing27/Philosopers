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
		eat(p);
	}
	pthread_exit(NULL);
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
		pthread_detach(t.phi->id_thread);
		usleep(100);
		i++;
	}
}
