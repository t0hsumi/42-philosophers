#include <philosophers.h>

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	print_actions(philo, PFORK);
	pthread_mutex_lock(philo->right);
	print_actions(philo, PFORK);
}

void	philo_eat(t_philo *philo)
{
	print_actions(philo, PEAT);
	philo->last_eat = m_time();
	usleep(philo->table->time_e * 1000);
	philo->neats++;
	if (philo->table->n_time_must_eat && \
			philo->neats == philo->table->n_time_must_eat)
		philo->neats = -1;
}

void	philo_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	philo_sleep(t_philo *philo)
{
	print_actions(philo, PSLEEP);
	usleep(philo->table->time_s * 1000);
}

void	philo_think(t_philo *philo)
{
	print_actions(philo, PTHINK);
}
