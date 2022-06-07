/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:44:34 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/07 14:11:20 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_atoi(const char	*str)
{
	int				i;
	long long int	num;

	num = 0;
	i = 0;
	if (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (i == 0)
		return (-1);
	return (num);
}

void freee(my_threads	*t)
{
	if (t->status)
		free(t->status);
	if (t->status_addr)
		free(t->status_addr);
	if (t->threads)
		free(t->threads);
	if (t->phil)
		free(t->phil);
}

int	check_info(my_threads t, int argc)
{
	if (argc == 5)
		t.num_eats = 0;
	if (t.num_ph < 2)
		return (0);
	if (t.num_eats < 1 && argc == 6)
		return (0);
	if (t.time_to_die <= 0 || t.time_to_eat <= 0 || t.time_to_sleep <= 0)
		return (0);
	return (1);
}

long long	get_time(void)
{
	struct timeval t;
	
	gettimeofday(&t, NULL);
	return(t.tv_sec * 1000 + t.tv_usec / 1000);
}
