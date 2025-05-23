/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:25:25 by tsomacha          #+#    #+#             */
/*   Updated: 2025/05/21 03:52:58 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Function declaration
*/
int	ft_set_forks(t_fork *forks, int size);
int	ft_set_table(t_table *table, char *argv[]);
int	ft_start(t_table *table, t_fork *forks, t_philo *philos, char *argv[]);
int	ft_set_philos(t_table *table, t_fork *forks, t_philo *philos, char *argv[]);

/**
 * Initializes the table structure with simulation parameters
 * Sets the number of philosophers and initial simulation flags
 * Initializes mutexes for death detection, writing, and meal tracking
 * Returns 1 on successful initialization, 0 if any mutex initialization fails
*/
int	ft_set_table(t_table *table, char *argv[])
{
	table->size = ft_atol(argv[1]);
	table->is_alive = 1;
	table->has_eaten = 0;
	if ((pthread_mutex_init(&table->lck_die, NULL)) != 0)
		return (ft_error("died lock initializing fail!"));
	if ((pthread_mutex_init(&table->lck_wrt, NULL)) != 0)
		return (ft_error("write lock initializing fail!"));
	if ((pthread_mutex_init(&table->lck_mel, NULL)) != 0)
		return (ft_error("meal lock initializing fail!"));
	return (0);
}

/**
 * Initializes the fork structures for the simulation
 * Assigns an ID and size to each fork
 * Initializes a mutex for each fork to handle locking during eating
 * Returns 1 on success, 0 if any mutex initialization fails
*/
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

/**
 * Initializes philosopher structures with simulation parameters
 * Sets philosopher IDs, time constraints (die, eat, sleep), and optional
 * meal limit
 * Assigns start and last meal times to current time
 * Sets initial values such as meals eaten and total number of philosophers
 * Assigns left and right forks
 * (with circular reference for the last philosopher)
 * Links shared simulation flags and mutexes from the table
 * Returns 0 after successful initialization
*/
int	ft_set_philos(t_table *table, t_fork *forks, t_philo *philos, char *argv[])
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

/**
 * Starts the dining philosophers simulation
 * Initializes the table, forks, and philosophers with provided arguments
 * Creates the observer thread to monitor philosopher states
 * Creates a thread for each philosopher to run their routine
 * Waits for all philosopher threads to finish using pthread_join
 * Waits for the observer thread to finish as well
 * Returns 1 on successful start and completion, 0 if any thread operation fails
*/
int	ft_start(t_table *table, t_fork *forks, t_philo *philos, char *argv[])
{
	int		i;
	int		size;

	i = 0;
	if (ft_set_table(table, argv))
		return (ft_error("table intializing fails!"));
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
	return (0);
}
