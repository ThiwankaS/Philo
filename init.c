/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:25:25 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/25 10:14:09 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 *ft_life function is the main loop which will take each philosopher through his life cycle.
 **/

int	ft_life(t_philo *philo)
{
	ft_think(philo);
	ft_eat(philo);
	ft_sleep(philo);
	return (1);
}
/**
*ft_flag functio is always check the is_alive value, default value set during the initializing
*statge in '1'. As soon as a philosopher died this value set to '0'.
*Synchronizing has made possible using the mutex_lock lck_die.
**/

int	ft_has_died(t_philo *philo)
{
	pthread_mutex_lock(philo->lck_die);
	if (*philo->is_alive)
	{
		pthread_mutex_unlock(philo->lck_die);
		return (1);
	}
	pthread_mutex_unlock(philo->lck_die);
	return (0);
}

int ft_has_eaten(t_philo *philo)
{
	pthread_mutex_lock(philo->lck_mel);
	if (*philo->has_eaten)
	{
		pthread_mutex_unlock(philo->lck_mel);
		return (0);
	}
	pthread_mutex_unlock(philo->lck_mel);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (ft_has_died(philo) && ft_has_eaten(philo))
	{
		ft_life(philo);
	}
	return (NULL);
}

int	ft_set_table(t_table *table, char *argv[])
{
	table->size = ft_atol(argv[1]);
	table->is_alive = 1;
	table->has_eaten = 0;
	if ((pthread_mutex_init(&table->lck_die, NULL)) != 0)
		return (0);
	if ((pthread_mutex_init(&table->lck_wrt, NULL)) != 0)
		return (0);
	if ((pthread_mutex_init(&table->lck_mel, NULL)) != 0)
		return (0);
	return (1);
}

int	ft_set_forks(t_fork *forks, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		forks[i].id = i + 1;
		forks[i].size = size;
		if ((pthread_mutex_init(&forks[i].fork, NULL)) != 0)
			return (0);
		i++;
	}
	return (1);
}

int ft_set_philos(t_table *table, t_fork *forks, t_philo *philos, char *argv[])
{
	int		i;
	int		size;
	size_t	time;

	i = 0;
	size = table->size;
	time = getcurrenttime();
	while (i < size)
	{
		philos[i].id = i + 1;
		philos[i].tm_die = ft_atol(argv[2]);
		philos[i].tm_eat = ft_atol(argv[3]);
		philos[i].tm_slp = ft_atol(argv[4]);
		if (argv[5])
			philos[i].meals = ft_atol(argv[5]);
		else
			philos[i].meals = -1;
		philos[i].tm_brn = time;
		philos[i].tm_lst = time;
		philos[i].size = size;
		philos[i].eaten = 0;
		philos[i].fork_l = &forks[i];
		if (i == size - 1)
			philos[i].fork_r = &forks[0];
		else
			philos[i].fork_r = &forks[i + 1];
		philos[i].is_alive = &table->is_alive;
		philos[i].has_eaten = &table->has_eaten;
		philos[i].lck_die = &table->lck_die;
		philos[i].lck_wrt = &table->lck_wrt;
		philos[i].lck_mel = &table->lck_mel;
		i++;
	}
	return (0);
}

int	ft_start(t_table *table, t_fork *forks, t_philo *philos, char *argv[])
{
	int		i;
	int		size;


	i = 0;
	ft_set_table(table, argv);
	size = table->size;
	ft_set_forks(forks, size);
	ft_set_philos(table, forks, philos, argv);
	if ((pthread_create(&table->checker, NULL, observer, philos)) != 0)
		return (0);
	i = 0;
	while (i < size)
	{
		if ((pthread_create(&philos[i].thread, NULL, routine, &philos[i])) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(table->checker, NULL) != 0)
		return (0);
	return (1);
}
