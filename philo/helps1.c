/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:44:34 by cnearing          #+#    #+#             */
/*   Updated: 2022/03/15 13:47:08 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_atoi(const char	*str)
{
	int				i;
	long long int	sign;
	long long int	num;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num < 0 && sign == -1)
			return (0);
		if (num < 0 && sign == 1)
			return (-1);
		i++;
	}
	return (num * sign);
}

void freee(my_threads	*t)
{
	int	i;

	if (t->status)
		free(t->status);
	if (t->status_addr)
		free(t->status_addr);
	i = t->num - 1;
	if (t->threads)
		free(t->threads);
}

int	t_init(my_threads	*t)
{
	t->threads = malloc(sizeof(pthread_t) * t->num);
	if (!t->threads)
		return (0);
	t->status = malloc(sizeof(int) * t->num);
	if (!t->status)
	{
		freee(t);
		return (0);
	}
	t->status_addr = malloc(sizeof(int) * t->num);
	if (!t->status_addr)
	{
		freee(t);
		return (0);
	}
}
