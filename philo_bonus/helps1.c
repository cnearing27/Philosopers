/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:44:34 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/28 16:44:30 by cnearing         ###   ########.fr       */
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
		return (0);
	return (num);
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

void	close_sem(t_s	*t)
{
	sem_close(t->forks);
	sem_close(t->writing);
	sem_unlink("/forks");
	sem_unlink("/write");
}

void	clean(t_s	*t)
{
	int	i;
	int	status;
	int	full;

	full = 0;
	i = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		status = status >> 8;
		if (status == 4)
			break ;
		if (status == 5)
			full++;
		if (full == t->num_ph)
			break ;
	}
	while (i < t->num_ph)
	{
		kill(t->phi[i].id_proc, 9);
		i++;
	}
	close_sem(t);
}
