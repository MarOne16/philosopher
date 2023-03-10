/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:01:04 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/10 23:01:19 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval		tp;
	size_t				milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_sleepms(size_t ms, t_philo *philo)
{
	size_t	curr;
	size_t	end;
	size_t	t1;
	size_t	t2;

	curr = get_time();
	end = curr + ms;
	while (get_time() < end)
	{
		t1 = get_time();
		usleep(10);
		t2 = get_time();
		philo->timedie -= t2 - t1;
	}
}

void	ft_eat(t_philo *philo)
{
	size_t	t4;
	size_t	t3;

	t3 = get_time();
	philo->kla -= 1;
	philo->timedie = philo->maxtime;
	printp(philo, " is eating\n", 3);
	ft_sleepms(philo->timeineat, philo);
	t4 = get_time();
	philo->current_time += t4 - t3;
}

void	ft_sleep(t_philo *philo)
{
	size_t	t4;
	size_t	t3;

	t3 = get_time();
	printp(philo, " is sleeping\n", 1);
	ft_sleepms(philo->timesleep, philo);
	t4 = get_time();
	philo->current_time += t4 - t3;
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
