/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philotools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:04:28 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/16 22:53:10 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_sleep(t_philo *philo)
{
	printp(philo->mainphilo, philo->id, "is sleeping", 3);
	ft_sleepms(philo->mainphilo->timesleep);
	printp(philo->mainphilo, philo->id, "is thinking", 4);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mainphilo->forks[philo->left_f]));
	pthread_mutex_lock(&(philo->mainphilo->forks[philo->right_f]));
	printp(philo->mainphilo, philo->id, "has taken a forks", 1);
	printp(philo->mainphilo, philo->id, "is eating", 2);
	pthread_mutex_lock(&(philo->time));
	philo->timedie = gettime_ms();
	pthread_mutex_unlock(&(philo->time));
	pthread_mutex_lock(&(philo->mainphilo->kill));
	philo->eat_count = philo->eat_count - 1;
	pthread_mutex_unlock(&(philo->mainphilo->kill));
	ft_sleepms(philo->mainphilo->timeeat);
	pthread_mutex_unlock(&philo->mainphilo->forks[philo->right_f]);
	pthread_mutex_unlock(&philo->mainphilo->forks[philo->left_f]);
}

int	checkeat(t_philo *philo)
{
	int	x;

	x = -1;
	while (++x < philo->mainphilo->max_philo)
	{
		if (philo[x].eat_count > 0)
			return (0);
	}
	philo->mainphilo->finish = 1;
	return (1);
}

size_t	gettime_ms(void)
{
	struct timeval		tp;
	size_t				ms;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000;
	ms += tp.tv_usec / 1000;
	return (ms);
}

void	ft_sleepms(size_t ms)
{
	size_t	curr;
	size_t	end;

	curr = gettime_ms();
	end = curr + ms;
	while (gettime_ms() < end)
		usleep(100);
}
