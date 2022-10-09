#include <philosophers.h>

void philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	print_actions(philo, PFORK);
}

void philo_eat(t_philo *philo)
{
	print_actions(philo, PEAT);
	philo->last_eat = m_time();
	m_sleep(philo->table->time_e);
	philo->neats++;
	if (philo->table->n_time_must_eat && philo->neats == philo->table->n_time_must_eat)
		philo->neats = -1;
}

void philo_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void philo_sleep(t_philo *philo)
{
	print_actions(philo, PSLEEP);
	m_sleep(philo->table->time_s);
}

void philo_think(t_philo *philo)
{
	print_actions(philo, PTHINK);
}
