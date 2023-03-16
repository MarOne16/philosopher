/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:56:02 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/16 22:53:19 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_atoi(char *str)
{
	size_t	x;
	size_t	z;
	size_t	i;

	x = 1;
	z = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			x *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		z *= 10;
		z += str[i] - '0';
		i++;
	}
	return (z * x);
}

int	checkarg(char **argv)
{
	int	i;
	int	x;

	i = 0;
	if (ft_atoi(argv[1]) == 0)
		return (1);
	while (argv[++i])
	{
		x = 0;
		while (argv[i][x])
		{
			if (argv[i][x] >= '0' && argv[i][x] <= '9')
				x++;
			else
				return (1);
		}
	}
	return (0);
}

void	clear_all(t_mainphilo *philo)
{
	int	i;

	i = 0;
	while (i < philo->max_philo)
	{
		if (philo->philo[i].th)
			pthread_detach(philo->philo[i].th);
		pthread_mutex_destroy(&(philo->philo[i].time));
		i++;
	}
	free(philo->philo);
	i = 0;
	while (i < philo->max_philo)
	{
		pthread_mutex_destroy(&(philo->forks[i]));
		i++;
	}
	free(philo->forks);
	pthread_mutex_destroy(&(philo->print));
	pthread_mutex_destroy(&(philo->kill));
}
