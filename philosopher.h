#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>

# define MAX 200

typedef pthread_mutex_t t_mutex;
typedef pthread_t t_thread;
typedef struct timeval t_timeval;

typedef struct s_fork
{
	int		id;
	int		size;
	t_mutex	fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			*is_alive;
	int			size;
	int			meals;
	size_t		tm_die;
	size_t		tm_eat;
	size_t		tm_slp;
	size_t		tm_brn;
	size_t		tm_lst;
	t_fork		*fork_l;
	t_fork		*fork_r;
	t_thread	thread;
	t_mutex		*lck_die;
	t_mutex		*lck_wrt;
}	t_philo;

typedef struct s_table
{
	int			is_alive;
	int			size;
	t_thread	checker;
	t_mutex		lck_die;
	t_mutex		lck_wrt;
}	t_table;

//utils.c
int		ft_error(char *text);
int		ft_usleep(size_t m_sec);
int		ft_print(t_philo *philo, char *str);
size_t	ft_strlen(char *str);
size_t	getcurrenttime(void);

//atol.c
long	ft_atol(const char *nptr);

//validate.c
int	ft_is_valid(char **argv, int argc);

//init.c
int	ft_start(t_table *table, t_fork *forks, t_philo *philo, char *argv[]);
int	ft_flag(t_philo *philo);

//actions.c
int	ft_sleep(t_philo *philo);
int	ft_think(t_philo *philo);
int	ft_eat(t_philo *philo);

//checks.c
void	*observer(void *arg);
int	ft_isalive(t_philo *philos, int size);

//exit.c
int	ft_exit(t_table *table, t_fork *forks,t_philo *philos);

#endif
