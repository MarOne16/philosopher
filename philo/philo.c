/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:01:04 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/11 14:56:17 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	gettime_ms(void)
{
	struct timeval		tp;
	size_t				ms;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000;
	ms += tp.tv_usec / 1000;
	return (ms);
}

void	ft_sleepms(size_t ms, t_philo *philo)
{
	size_t	curr;
	size_t	end;
	size_t	t1;
	size_t	t2;

	curr = gettime_ms();
	end = curr + ms;
	while (gettime_ms() < end)
	{
		t1 = gettime_ms();
		usleep(100);
		t2 = gettime_ms();
		philo->timedie += ((t2 - t1));
	}
}

void	ft_eat(t_philo *philo)
{
	size_t	t4;
	size_t	t3;

	t3 = gettime_ms();
	philo->kla -= 1;
	philo->timedie = 0;
	printp(philo, " is eating\n", 3);
	ft_sleepms(philo->timeineat, philo);
	t4 = gettime_ms();
	philo->current_time += t4 - t3;
}

void	ft_sleep(t_philo *philo)
{
	size_t	t4;
	size_t	t3;

	t3 = gettime_ms();
	printp(philo, " is sleeping\n", 1);
	ft_sleepms(philo->timesleep, philo);
	t4 = gettime_ms();
	philo->current_time += t4 - t3;
	printp(philo, " is thinking\n", 2);
}

int	main(int argc, char *argv[])
{
	int				i;
	int				x;
	t_philo			*philo;
	pthread_mutex_t	print;

	if ((argc == 5 || argc == 6) && !checkarg(argv))
	{
		x = -1;
		philo = malloc(sizeof(t_philo));
		i = ft_atoi(argv[1]);
		if (pthread_mutex_init(&print, 0x0))
			perror("Failed to init thread");
		while (++x < i)
			if (pthread_mutex_init(&philo[x].left_f, 0x0))
				perror("Failed to init thread");
		if (argc == 6)
			feedthread(philo, argv, &print, ft_atoi(argv[5]));
		else
			feedthread(philo, argv, &print, SIZE_MAX);
		runthread(philo, i);
	}
	else
		printf("Error\n");
	return (0);
}
