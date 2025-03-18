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

typedef struct s_philo
{
	int	id;
	size_t tm_die;
	size_t tm_eat;
	size_t tm_slp;
	t_thread thread;
}	t_philo;

typedef struct s_table
{
	int	is_eaten;
	int	size;
}	t_tabel;

//utils.c
int ft_error(char *text);
size_t ft_strlen(char *str);

//atol.c
long	ft_atol(const char *nptr);

//validate.c
int ft_is_valid(char **argv, int argc);

#endif
