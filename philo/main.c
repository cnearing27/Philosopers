#include "philo.h"

void	*new_philo(void	*args)
{
	long long int	n;
	n = (long long int)args;
	printf("Created new Philo! %d\n", n);
	return (0);
}

int	main(int argc, char	**argv)
{
	my_threads		t;
	long long int	i;

	if (argc != 6)
		return (0);
	t.num = ft_atoi(argv[1]);
	if (t.num <= 0)
		return (0);
	if (t_init(&t) == 0)
		return (0);
	i = 0;
	while (i < t.num)
	{
		t.status[i] = pthread_create(t.threads, NULL, new_philo, (void *)i);
		t.status[i] = pthread_join(*t.threads, (void **)&t.status_addr[i]);
		i++;
	}
}
