/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philotools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:49:55 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/17 13:10:29 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initmutex(t_mainphilo *philo, char **argv)
{
	int	i;		

	philo->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!philo->forks || pthread_mutex_init(&(philo->kill), NULL) || \
		pthread_mutex_init(&(philo->print), NULL))
		perror("-->");
	i = -1;
	while (++i < philo->max_philo)
		pthread_mutex_init(&philo->forks[i], NULL);
}

void	printp(t_mainphilo *mainphilo, int id, char *msg, int x)
{
	long long	now;

	if (lockphilo(mainphilo))
	{
		pthread_mutex_lock(&(mainphilo->print));
		now = gettime_ms();
		if (x == 1)
			printf(AC_MAGENTA"%lld ms %d %s\n", \
			now - mainphilo->current_time, id, msg);
		else if (x == 2)
			printf(AC_WHITE"%lld ms %d %s\n", \
			now - mainphilo->current_time, id, msg);
		else if (x == 3)
			printf(AC_BLUE"%lld ms %d %s\n", \
			now - mainphilo->current_time, id, msg);
		else if (x == 4)
			printf(AC_YELLOW"%lld ms %d %s\n", \
			now - mainphilo->current_time, id, msg);
		pthread_mutex_unlock(&(mainphilo->print));
	}
}

void	feedphilo(t_mainphilo *mainphilo, char **argv, long long eat)
{
	int	i;

	i = -1;
	mainphilo->philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!(mainphilo->philo))
		return ;
	while (++i < mainphilo->max_philo)
	{
		mainphilo->philo[i].mainphilo = mainphilo;
		mainphilo->philo[i].th = NULL;
		mainphilo->philo[i].id = i + 1;
		mainphilo->philo[i].left_f = i;
		mainphilo->philo[i].right_f = (i + 1) % ft_atoi(argv[1]);
		mainphilo->philo[i].eat = eat;
		mainphilo->philo[i].timedie = gettime_ms();
		pthread_mutex_init(&(mainphilo->philo[i].time), NULL);
	}
	return ;
}

void	feedthread(t_mainphilo *mainphilo, char **argv)
{
	mainphilo->max_philo = ft_atoi(argv[1]);
	mainphilo->maxtime = ft_atoi(argv[2]);
	mainphilo->timeeat = ft_atoi(argv[3]);
	mainphilo->timesleep = ft_atoi(argv[4]);
	mainphilo->current_time = gettime_ms();
	mainphilo->finish = 0;
	initmutex(mainphilo, argv);
}

int	lockphilo(t_mainphilo *mainphilo)
{
	pthread_mutex_lock(&(mainphilo->kill));
	if (mainphilo->finish == 1)
	{
		pthread_mutex_unlock(&mainphilo->kill);
		return (0);
	}
	pthread_mutex_unlock(&mainphilo->kill);
	return (1);
}
