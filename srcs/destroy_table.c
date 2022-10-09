#include <philosophers.h>
#include <pthread.h>

void destroy_table(t_table *table)
{
	int i;

	i = -1;
	free(table->philos);
	table->philos = NULL;
	while (++i < table->n_philos)
		pthread_mutex_destroy(table->forks + i);
	free(table->forks);
	table->forks = NULL;
}
