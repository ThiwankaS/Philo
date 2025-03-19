/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:25:25 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/19 05:11:51 by tsomacha         ###   ########.fr       */
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
	t_philo *philo = (t_philo *) arg;
	while(*philo->is_alive)
	{
		ft_life(philo);
	}
	return (NULL);
}

int	ft_isalive(t_philo *philos, int size)
{
	int i = 0;
	while (i < size)
	{
		if (getcurrenttime() - philos[i].tm_lst > philos[i].tm_die)
		{
			*philos[i].is_alive = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

void	*observer(void *arg)
{
	int	size;
	int	flag = 1;
	t_philo *philos = (t_philo *) arg;
	size = philos[0].size;
	while (flag)
	{
		if(!ft_isalive(philos, size))
			flag = 0;
	}
	return (NULL);
}

int	ft_set_table(t_table *table, char *argv[])
{
	table->size = ft_atol(argv[1]);
	table->is_alive = 1;
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
		if ((pthread_mutex_init(&forks[i].fork, NULL))!= 0)
			return (0);
		i++;
	}
	return (1);
}

int ft_start(t_table *table, t_fork *forks, t_philo *philos, char *argv[])
{
	int i;
	int size;
	size_t	time = getcurrenttime();
	ft_set_table(table, argv);
	i = 0;
	size = table->size;
	ft_set_forks(forks, size);
	while(i < size)
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
	while ( i < size)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}

	if (pthread_join(table->checker, NULL) != 0)
		return (0);
	return (1);
}
