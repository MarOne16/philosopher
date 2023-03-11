/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkphilo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:46:22 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/11 15:42:13 by mqaos            ###   ########.fr       */
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
		t3 = gettime_ms();
		t1 = gettime_ms();
		pthread_mutex_lock(&philo->left_f);
		pthread_mutex_lock(philo->right_f);
		t2 = gettime_ms();
		t4 = gettime_ms();
		philo->timedie += ((t4 - t3));
		philo->current_time += t2 - t1;
		printp(philo, " taking a forks\n", 4);
		ft_eat(philo);
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(&philo->left_f);
		ft_sleep(philo);
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
			if ((philo[x].timedie >= philo->maxtime) || (i <= 1))
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
	size_t			x;
	pthread_t		*th;
	pthread_mutex_t	pa;

	th = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (!th)
		printf("Failed to allocate memory for thread array");
	x = -1;
	while (++x < (ft_atoi(argv[1])))
	{
		if (pthread_mutex_init(&pa, NULL))
			printf("Failed to initialize mutex");
		philo[x].th = th[x];
		philo[x].id = x + 1;
		philo[x].kla = kla;
		philo[x].print = print;
		philo[x].right_f = &philo[(x + 1) % ft_atoi(argv[1])].left_f;
		philo[x].current_time = 0;
		philo[x].maxtime = ft_atoi(argv[2]);
		philo[x].timedie = 0;
		philo[x].timesleep = ft_atoi(argv[4]);
		philo[x].timeineat = ft_atoi(argv[3]);
	}
	free(th);
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

void	destroy(t_philo *philo, int i)
{
	while (--i)
		pthread_mutex_destroy(&philo[i].left_f);
	free(philo);
}
