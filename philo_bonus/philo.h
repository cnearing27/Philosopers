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
# include <sys/wait.h> // waitpid
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>

typedef struct philosophers
{
	int					id;
	int					eat_num;
	unsigned long long	last_eat;
	pid_t				id_proc;
	pthread_t			id_thread;
	struct my_struct	*info;
}	t_philo;

typedef struct my_struct
{
	unsigned long long	start_time;
	int					num_ph;
	unsigned long long	time_to_die;
	long long			time_to_eat;
	long long int		time_to_sleep;
	long long int		num_eats;
	int					is_died;
	sem_t				*status_eat;
	sem_t				*forks;
	sem_t				*writing;
	t_philo				phi[200];
}	t_s;

long long int		ft_atoi(const char	*str);
char				*ft_itoa(int n);
int					t_init(t_s	*t, int argc, char	**argv);
void				freee(t_s	*t);
void				*new_philo(void	*args);
int					check_info(t_s t, int argc);
int					init_philos(t_s *t);
unsigned long long	get_time(void);
int					mutex_init(t_s	*t);
void				print_status(t_s	*t, int i, char	*line);
void				eat(t_philo	*p);
void				w_for(unsigned long long w_start, unsigned long long w_f);
void				clean(t_s	*t);
void				*start_spectator(void	*arg);

#endif
