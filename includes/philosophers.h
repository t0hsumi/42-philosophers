#ifndef PHILOSOPERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_table t_table;

typedef struct s_philo
{
	int id;
	pthread_t thread;
	long long last_eat;
	int neats;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	t_table *table;
} t_philo;

typedef struct s_table
{
	int n_philos;
	int time_d;
	int time_e;
	int time_s;
	int n_time_must_eat;
	bool is_dead;
	long long start;
	t_philo *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
} t_table;

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

int check_args(int argc, char **argv);

int init_table(int argc, char **argv, t_table *table);

int destroy_table(t_table *table);
long	ft_atoi(const char *nptr);
int ft_error(char *msg);
long long m_time(void);
void print_actions(t_philo *philo, int msg);

void philo_think(t_philo *philo);
void philo_sleep(t_philo *philo);
void philo_drop_forks(t_philo *philo);
void philo_eat(t_philo *philo);
void philo_take_forks(t_philo *philo);
void *die_check(void *arg);
int launch_simulation(t_table *table);
# endif
