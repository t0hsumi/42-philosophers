#include <philosophers.h>

int ft_error(char *msg)
{
	printf("%s\n", msg);
	return 1;
}

long long m_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void m_sleep(int time)
{
	usleep(time * 1000);
}

void print_actions(t_philo *philo, char *msg)
{
	printf("%lld %d %s\n", m_time(), philo->id, msg);
}
