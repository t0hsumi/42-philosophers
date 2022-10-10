#include <philosophers.h>

static int is_full_up(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->n_philos)
		if ((table->philos + i)->neats >= 0)
			return 0;
	return 1;
}

static void observe(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->n_philos)
		if ((table->philos + i)->last_eat == 0)
			(table->philos + i)->last_eat = table->start;
	i = -1;
	while (++i < table->n_philos)
	{
		if ((table->philos + i)->neats >= 0)
		{
			if (table->time_d < m_time() - (table->philos + i)->last_eat)
			{
				print_actions(table->philos + i, PDIED);
			}
		}
	}
	i = -1;
	if (table->is_dead)
		while (++i < table->n_philos)
			pthread_mutex_unlock(table->forks + i);
}

void *die_check(void *arg)
{
	t_table *table;

	table = (t_table *)arg;
	while (1)
	{
		usleep(100);
		if (table->is_dead)
			break;
		if (is_full_up(table))
			break;
		observe(table);
	}
	return (NULL);
}
