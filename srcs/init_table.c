#include <philosophers.h>

static void	init_philosophers(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->n_philos)
	{
		philo = table->philos + i;
		philo->last_eat = 0;
		philo->neats = 0;
		philo->id = i + 1;
		philo->left = table->forks + i;
		if (i != table->n_philos - 1)
			philo->right = table->forks + i + 1;
		philo->table = table;
	}
	philo->right = table->forks;
}

static int	allocate(t_table *table)
{
	int	i;

	table->philos = malloc(table->n_philos * sizeof(t_philo));
	if (!table->philos)
		return (ft_error(EMALLOC));
	table->forks = malloc(table->n_philos * sizeof(pthread_mutex_t));
	if (!table->forks)
	{
		free(table->philos);
		table->philos = NULL;
		return (ft_error(EMALLOC));
	}
	i = -1;
	while (++i < table->n_philos)
		if (pthread_mutex_init(table->forks + i, NULL))
			return (ft_error(EMUTEX));
	if (pthread_mutex_init(&table->print, NULL))
		return (ft_error(EMUTEX));
	return (0);
}

int	init_table(int argc, char **argv, t_table *table)
{
	table->n_philos = ft_atoi(argv[1]);
	table->time_d = ft_atoi(argv[2]);
	table->time_e = ft_atoi(argv[3]);
	table->time_s = ft_atoi(argv[4]);
	if (argc == 6)
		table->n_time_must_eat = ft_atoi(argv[5]);
	else
		table->n_time_must_eat = 0;
	table->is_dead = false;
	if (allocate(table))
		return (destroy_table(table));
	init_philosophers(table);
	return (0);
}
