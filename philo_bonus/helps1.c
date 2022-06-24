/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:44:34 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/24 13:33:45 by cnearing         ###   ########.fr       */
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
	if (i == 0 || str[i])
		return (-1);
	return (num);
}

void	freee(t_s	*t)
{
	if (t->forks)
		free(t->forks);
	if (t->phi)
		free(t->phi);
}

unsigned long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	print_status(t_s	*t, int i, char	*line)
{
	sem_wait(t->writing);
	if (!(t->is_died))
		printf("%lld %d %s\n", get_time() - t->start_time, i, line);
	sem_post(t->writing);

}

void	clean(t_s	*t)
{
	int	i;

	sem_close(t->status_eat);
	i = 0;
	while (i < t->num_ph)
	{
		sem_close(t->forks[i]);
		i++;
	}
	sem_close(t->writing);
	freee(t);
}
