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
	unsigned long long	last_eat;
	pthread_t			id_thread;
	struct t_threads	*info;
}	t_philo;

typedef struct t_threads
{
	unsigned long long	start_time;
	int					num_ph;
	unsigned long long	time_to_die;
	long long			time_to_eat;
	long long int		time_to_sleep;
	long long int		num_eats;
	long long int		all_eats;
	int					is_died;
	pthread_mutex_t		forks[200];
	pthread_mutex_t		writing;
	t_philo				phi[200];
}	t_threads;

long long int		ft_atoi(const char	*str);
int					t_init(t_threads	*t, int argc, char	**argv);
void				*new_philo(void	*args);
int					check_info(t_threads t, int argc);
int					init_philos(t_threads *t);
unsigned long long	get_time(void);
int					mutex_init(t_threads	*t);
void				print_status(t_threads	*t, int i, char	*line);
void				eat(t_philo	*p);
void				w_for(unsigned long long w_start, unsigned long long w_f);
void				clean(t_threads	*t);
void				start_spectator(t_threads	*t);
void				*start_emulation(void *arg);

#endif
