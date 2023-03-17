/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:01:04 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/17 15:21:04 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (lockphilo(philo->mainphilo))
	{
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
}

void	die_check(t_philo *philo)
{
	long long	now;

	now = gettime_ms();
	if ((philo->mainphilo->finish == 0 && (now - philo->timedie \
		== philo->mainphilo->maxtime)))
	{
		philo->mainphilo->finish = 1;
		pthread_mutex_lock(&philo->mainphilo->print);
		printf(AC_RED"%lld ms philo %d died\n", \
		now - philo->mainphilo->current_time,
			philo->id);
		pthread_mutex_unlock(&(philo->mainphilo->print));
	}
}

void	*check_check(void *arg)
{
	t_philo		*philo;

	philo = arg;
	while (lockphilo(philo->mainphilo))
	{
		usleep(100);
		pthread_mutex_lock(&(philo->mainphilo->kill));
		pthread_mutex_lock(&(philo->time));
		die_check(philo);
		if (checkeat(philo) && philo->mainphilo->finish != 1)
		{
			philo->mainphilo->finish = 1;
			pthread_mutex_lock(&(philo->mainphilo->print));
			printf(AC_GREEN"All philosophers ate their meals\n");
			pthread_mutex_unlock(&(philo->mainphilo->print));
		}
		pthread_mutex_unlock(&(philo->time));
		pthread_mutex_unlock(&(philo->mainphilo->kill));
	}
	return (NULL);
}

void	runthread(t_mainphilo *mainphilo)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < mainphilo->max_philo)
	{
		pthread_create(&(mainphilo->philo[i].th), NULL, &routine, \
			&(mainphilo->philo[i]));
		pthread_create(&monitor, NULL, &check_check, \
			&(mainphilo->philo[i]));
		pthread_detach(monitor);
		i++;
	}
	i = 0;
	while (i < mainphilo->max_philo)
		pthread_join(mainphilo->philo[i++].th, NULL);
}

int	main(int argc, char *argv[])
{
	t_mainphilo		philo;

	if ((argc == 5 || argc == 6) && !checkarg(argv))
	{
		if (ft_atoi(argv[1]) == 1)
		{
			printf(AC_RED"0 ms 1 has taken a forks\n1 ms philo 1 died\n");
			return (0);
		}
		feedthread(&philo, argv);
		if (argc == 5)
			feedphilo(&philo, argv, INT32_MAX);
		else
			feedphilo(&philo, argv, ft_atoi(argv[5]));
		runthread(&philo);
		clear_all(&philo);
	}
	else
		printf(AC_BLACK"Error\n");
	return (0);
}
