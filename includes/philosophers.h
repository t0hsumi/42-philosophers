/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:28:16 by tohsumi           #+#    #+#             */
/*   Updated: 2022/10/10 18:28:19 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_table	t_table;

/*
   Parameters
   id         philosophers id.
   thread     each philosopher should be a thread.
   last_eat   time[ms] when philosopher last ate meal.
   neats      number of time philosopher ate meal.
   left       left-side fork.
   right      right-side fork.
   table      pointer to the table information.
   */
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long long		last_eat;
	int				neats;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_table			*table;
}	t_philo;

/*
   Parameters
   n_philos          number of philosophers.
   time_d            time to die.
   time_e            time to eat.
   time_s            time to sleep.
   n_time_must_eat   number of times each philosopher must eat.
   is_dead           flag if the philosophers is dead or not.
   start             time[ms] when start simulation.
   philos            pointer to each philosopher.
   forks             pointer to all the forks.
   print             mutex in order to display timestamp in chronological order
                     and not to display any log when one of philosophers dead.
   */
typedef struct s_table
{
	int				n_philos;
	int				time_d;
	int				time_e;
	int				time_s;
	int				n_time_must_eat;
	bool			is_dead;
	long long		start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_table;

# define USEERR "[usage] ./philo number_of_philosophers \
	time_to_die time_to_eat time_to_sleep \
	[number_of_times_each_philosophers_must_eat]"

# define EMUTEX "pthread_mutex_init() failed"
# define EMALLOC "malloc() failed"
# define ETHREAD "pthread_create() failed"
# define EJOIN "pthread_join() failed"

enum e_actions
{
	PFORK,
	PEAT,
	PTHINK,
	PSLEEP,
	PDIED
};

// check cmdline arguments.
int			check_args(int argc, char **argv);

// initialize table.
// This function contains reserving resources that must be released later.
int			init_table(int argc, char **argv, t_table *table);
int			launch_simulation(t_table *table);

// release resources.
int			destroy_table(t_table *table);

/* philosophers' actions */
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_drop_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_take_forks(t_philo *philo);

/* observer's actions */
void		*die_check(void *arg);

/* utils */
// similar to atoi() but return LONG_MIN in case of error.
long		ft_atoi(const char *nptr);

// stdout error message.
int			ft_error(char *msg);

// return timestamp[ms].
long long	m_time(void);

// stdout timestamp
void		print_actions(t_philo *philo, int msg);

#endif
