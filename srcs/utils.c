/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:27:49 by tohsumi           #+#    #+#             */
/*   Updated: 2022/10/10 18:27:49 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	ft_error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

long long	m_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_actions(t_philo *philo, int msg)
{
	long long	time;

	pthread_mutex_lock(&philo->table->print);
	if (!philo->table->is_dead)
	{
		time = m_time() - philo->table->start;
		if (msg == PFORK)
			printf("%lld %d has taken a fork\n", time, philo->id);
		else if (msg == PEAT)
			printf("%lld %d is eating\n", time, philo->id);
		else if (msg == PSLEEP)
			printf("%lld %d is sleeping\n", time, philo->id);
		else if (msg == PTHINK)
			printf("%lld %d is thinking\n", time, philo->id);
		else
		{
			printf("%lld %d died\n", time, philo->id);
			philo->table->is_dead = true;
		}
	}
	pthread_mutex_unlock(&philo->table->print);
}
