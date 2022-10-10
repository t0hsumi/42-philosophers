#include <philosophers.h>

static void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		usleep(200);
	while (1)
	{
		if (philo->table->is_dead)
			break ;
		philo_take_forks(philo);
		philo_eat(philo);
		philo_drop_forks(philo);
		if (philo->neats < 0)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	launch_simulation(t_table *table)
{
	pthread_t	observer;
	int			i;

	i = -1;
	table->start = m_time();
	while (++i < table->n_philos)
		if (pthread_create(&(table->philos + i)->thread, NULL, &simulation, \
					table->philos + i))
			return (ft_error(ETHREAD));
	if (pthread_create(&observer, NULL, &die_check, table))
		return (ft_error(ETHREAD));
	i = -1;
	while (++i < table->n_philos)
		if (pthread_join((table->philos + i)->thread, NULL))
			return (ft_error(EJOIN));
	if (pthread_join(observer, NULL))
		return (ft_error(EJOIN));
	return (0);
}
