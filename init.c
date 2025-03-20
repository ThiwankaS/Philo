/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:25:25 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/20 05:42:49 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_life(t_philo *philo)
{
	ft_think(philo);
	ft_eat(philo);
	ft_sleep(philo);
	return (1);
}

void	*routine(void *arg)
{
	int		flag;
	t_philo	*philo;

	philo = (t_philo *) arg;
	flag = 1;
	while (flag)
	{
		ft_life(philo);
		pthread_mutex_lock(philo->lck_die);
		if (!*philo->is_alive)
			flag = 0;
		pthread_mutex_unlock(philo->lck_die);
	}
	return (NULL);
}

int	ft_set_table(t_table *table, char *argv[])
{
	table->size = ft_atol(argv[1]);
	table->is_alive = 1;
	if ((pthread_mutex_init(&table->lck_die, NULL)) != 0)
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

int	ft_start(t_table *table, t_fork *forks, t_philo *philos, char *argv[])
{
	int		i;
	int		size;
	size_t	time;

	i = 0;
	time = getcurrenttime();
	ft_set_table(table, argv);
	size = table->size;
	ft_set_forks(forks, size);
	while (i < size)
	{
		philos[i].id = i + 1;
		philos[i].tm_die = ft_atol(argv[2]);
		philos[i].tm_eat = ft_atol(argv[3]);
		philos[i].tm_slp = ft_atol(argv[4]);
		philos[i].tm_brn = time;
		philos[i].tm_lst = time;
		philos[i].size = size;
		philos[i].fork_l = &forks[i];
		if (i == size - 1)
			philos[i].fork_r = &forks[0];
		else
			philos[i].fork_r = &forks[i + 1];
		philos[i].is_alive = &table->is_alive;
		philos[i].lck_die = &table->lck_die;
		i++;
	}
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
