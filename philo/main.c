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
		pthread_detach(t.phi[i].id_thread);
		t.phi[i].last_eat = get_time();
		i++;
	}
	start_spectator(&t);
	clean(&t);
}
