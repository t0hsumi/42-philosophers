#include <philosophers.h>

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

/*
    ft_atoi() is similar to atoi() in libc, except that it returns LONG_MIN
	when input char contains non digital number or overflow.
	In addition, this function doesn't manage spaces at the beginning of input.
*/
long	ft_atoi(const char *nptr)
{
	long int	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i++] == '-')
			sign = -1;
	}
	while (ft_isdigit(nptr[i]))
	{
		res = res * 10 + (int)(nptr[i] - '0');
		if (INT_MAX + 1L < res)
			return (LONG_MIN);
		i++;
	}
	res *= sign;
	if (res < INT_MIN || INT_MAX < res || nptr[i] != 0 || i == 0)
		return (LONG_MIN);
	else
		return (res);
}
