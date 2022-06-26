/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:44:34 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/26 20:42:46 by cnearing         ###   ########.fr       */
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
	sem_close(t->forks);
	sem_close(t->writing);
	sem_unlink("/eat");
	sem_unlink("/forks");
	sem_unlink("/write");
	freee(t);
}
