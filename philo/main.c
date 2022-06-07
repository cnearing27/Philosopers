#include "philo.h"

void	*start_emulation(void *arg)
{
	my_threads	t;

	t = (my_threads)t;
	printf("%lld created\n", get_time() - t.start_time);
	printf("AFTER start time = %lld\n", t.start_time);
	pthread_exit(NULL);
}

int	main(int argc, char	**argv)
{
	my_threads		t;
	long long int	i;

	if (argc != 5 && argc != 6)
		return (0);
	if (argc == 6)
		t.num_eats = ft_atoi(argv[5]);
	t.num_ph = ft_atoi(argv[1]);
	t.time_to_die = ft_atoi(argv[2]);
	t.time_to_eat = ft_atoi(argv[3]);
	t.time_to_sleep = ft_atoi(argv[4]);
	if (check_info(t, argc) == 0)
		return (0);
	if (t_init(&t) == 0)
		return (0);
	i = 0;
	init_philos(&t);
	printf("BEFORE start time = %lld\n", t.start_time);
	while (i < t.num_ph)
	{
		pthread_create(t.threads, 0, start_emulation, (void *)&t);
		pthread_join(*t.threads, (void **)&t.status_addr[i]);
		//init
		//wait
		//eat
		//sleep
		i++;
	}
	printf("all's OK!\n");
}
