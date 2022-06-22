/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:13:12 by cnearing          #+#    #+#             */
/*   Updated: 2022/06/15 16:13:12 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct philosophers
{
	int					id;
	int					eat_num;
	int					fork_left;
	int					fork_right;
	unsigned long		last_eat;
	pthread_t			id_thread;
	struct t_threads	*info;
}	t_philo;

typedef struct t_threads
{
	unsigned long long	start_time;
	long long int		num_ph;
	long long int		time_to_die;
	long long int		time_to_eat;
	long long int		time_to_sleep;
	long long int		num_eats;
	long long int		all_eats; // + (new attribute)
	int					is_died;
	pthread_mutex_t		status_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing;
	t_philo				*phi;
}	t_threads;

long long int		ft_atoi(const char	*str);
int					t_init(t_threads	*t, int argc, char	**argv);
void				freee(t_threads	*t);
void				*new_philo(void	*args);
int					check_info(t_threads t, int argc);
void				init_philos(t_threads *t);
unsigned long  long	get_time(void);
void				mutex_init(t_threads	*t);
void				print_status(t_threads	*t, int i, char	*line);
void				eat(t_philo	*p);
void				clean(t_threads	*t); // + (new in helps1.c)

#endif
