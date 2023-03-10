/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkphilo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:46:22 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/10 22:56:08 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routin(void *arg)
{
	t_philo	*philo;
	size_t	t1;
	size_t	t2;
	size_t	t3;
	size_t	t4;

	philo = (t_philo *) arg;
	while (1)
	{
		t3 = get_time();
		t1 = get_time();
		pthread_mutex_lock(&philo->left_f);
		pthread_mutex_lock(philo->right_f);
		t4 = get_time();
		philo->timedie -= t4 - t3;
		t2 = get_time();
		philo->current_time += t2 - t1;
		printp(philo, " taking a forks\n", 4);
		ft_eat(philo);
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(&philo->left_f);
		ft_sleep(philo);
		printp(philo, " is thinking\n", 2);
	}
	return (NULL);
}

void	runthread(t_philo *philo, int i)
{
	int	x;

	x = -1;
	while (++x < i)
		pthread_create(&philo[x].th, NULL, &routin, &philo[x]);
	while (1)
	{
		x = -1;
		while (++x < i)
		{
			if ((philo[x].timedie <= 0) || (i <= 1))
			{
				pthread_mutex_lock(philo->print);
				printf(AC_RED "%zu ms philo %d die\n",
					philo[x].current_time, philo[x].id);
				return ;
			}
			else if (!checkkla(philo, i))
			{
				pthread_mutex_lock(philo->print);
				printf(AC_GREEN"all philo eats\n");
				return ;
			}
		}
	}
}

void	feedthread(t_philo *philo, char **argv,
pthread_mutex_t *print, size_t kla)
{
	int				i;
	int				x;
	pthread_t		th[ft_atoi(argv[1])];
	pthread_mutex_t	pa;

	x = -1;
	i = ft_atoi(argv[1]);
	while (++x < i)
	{
		if (pthread_mutex_init(&pa, NULL))
			perror("Failed to init thread");
		philo[x].th = th[x];
		philo[x].id = x + 1;
		philo[x].kla = kla;
		philo[x].print = print;
		philo[x].right_f = &philo[(x + 1) % i].left_f;
		philo[x].current_time = 0;
		philo[x].maxtime = ft_atoi(argv[2]);
		philo[x].timedie = philo[x].maxtime;
		philo[x].timesleep = ft_atoi(argv[4]);
		philo[x].timeineat = ft_atoi(argv[3]);
	}
}

int	checkkla(t_philo *philo, int i)
{
	int	x;

	x = i;
	while (x)
	{
		if (philo[x].kla > 0)
			return (1);
		x--;
	}
	return (0);
}
