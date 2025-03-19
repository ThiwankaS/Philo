/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:15:29 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/19 04:40:50 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_error(char *text)
{
	size_t	len;

	len = ft_strlen(text);
	write(2, " ERROR : [ ", 11);
	write(2, text, len);
	write(2, " ]\n", 3);
	return (1);
}

size_t	getcurrenttime(void)
{
	t_timeval	time;
	size_t		m_sec;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	m_sec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (m_sec);
}

int	ft_usleep(size_t m_sec)
{
	size_t	time;

	time = getcurrenttime();
	while (getcurrenttime() - time < m_sec)
		usleep(500);
	return (1);
}

int	ft_print(t_philo *philo, char *str)
{
	size_t	time;
	time = getcurrenttime() - philo->tm_brn;
	printf("%zu %d %s\n", time, philo->id, str);
	return (1);
}
