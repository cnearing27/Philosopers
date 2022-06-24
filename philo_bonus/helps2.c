#include "philo.h"

static int	decs(long	n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ten_pow(int	n)
{
	int	i;

	i = 1;
	while (n > 0)
	{
		i *= 10;
		n--;
	}
	return (i);
}

static void	fill_in(char	*res, long	n, int i, int	decs)
{
	int	t;

	t = ten_pow(decs - 1);
	while (t > 0)
	{
		res[i] = n / t + '0';
		n %= t;
		t /= 10;
		i++;
	}
	res[i] = '\0';
}

char	*ft_itoa(int	n)
{
	char	*res;
	int		d;

	d = decs(n);
	res = malloc(sizeof(char) * (d + 1));
	if (!res)
		return (0);
	fill_in(res, n, 0, d);
	return (res);
}