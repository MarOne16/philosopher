/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:01:04 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/09 16:42:35 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


size_t	maxtime;
size_t	timeeat;
size_t	timesleep;
int					die = 1;

size_t    get_time(void)
{
	struct timeval    tp;
	size_t        milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void    ft_sleepms(size_t ms)
{
    size_t    curr;
    size_t    end;

    curr = get_time();
    end = curr + ms;
    while (get_time() < end)
        usleep(100);
}

void	*checkdeath(void *thread)
{
	t_th	*philo = (t_th *)thread;
	int	x;
	while (1)
	{
		pthread_mutex_lock(philo->print);
		if (philo->timedie >= philo->maxtime)
		{
			printp(philo,"die");
			pthread_mutex_unlock(philo->print);
			return NULL;
		}
		pthread_mutex_unlock(philo->print);
	}
}

void	ft_eat(t_th *philo)
{
	philo->timedie = 0;
	size_t t1 = get_time();
	printp(philo," is eat\n");
	ft_sleepms(philo->timeineat);
	size_t t2 = get_time();
	philo->current_time += t2 - t1;
	philo->timedie += t2 - t1;
	
}
void	ft_sleep(t_th *philo)
{
	size_t t1 = get_time();
	printp(philo," sleep\n");
	ft_sleepms(philo->timesleep);
	size_t t2 = get_time();
	philo->timedie += t2 - t1;
	philo->current_time += t2 - t1;
	printp(philo," think\n");
}

void	*routin(void *arg)
{
	t_th	*philo = (t_th *)arg;
	if (philo->id % 2)
		ft_sleepms(2);
	while (die)
	{
		pthread_mutex_lock(philo->left_f);
		pthread_mutex_lock(philo->right_f);
		printp(philo," taking a forks\n");
		ft_eat(philo);
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
		ft_sleep(philo);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc == 5)
	{
		int i = ft_atoi(argv[1]);
		pthread_t	th[i + 1];
		int x = -1;
		philo_t	*philo = malloc(sizeof(philo_t));
		philo->pause = malloc(sizeof(pthread_mutex_t)*i);
		philo->list = malloc(sizeof(t_th) * i);
		pthread_mutex_t	print;
		if(pthread_mutex_init(&print,NULL))
			perror("Failed to init thread");
		while (++x < i)
		{
			pthread_mutex_t	pa;
			if(pthread_mutex_init(&pa,NULL))
				perror("Failed to init thread");
			philo->pause[x] = pa;
			philo->print = print;
			philo->list[x].print = &print;
			philo->list[x].kla = 1;
			philo->list[x].timedie = 0;
			philo->list[x].current_time = 0;
			philo->list[x].maxtime = ft_atoi(argv[2]);
			philo->list[x].id = x + 1;
			philo->list[x].kla = 1;
			philo->list[x].th = th[x];
			philo->list[x].timesleep = ft_atoi(argv[4]);
			philo->list[x].timeineat = ft_atoi(argv[3]);
		}
		x = -1;
		while (++x < i)
		{
			philo->list[x].left_f = &philo->pause[x];
			philo->list[x].right_f = &philo->pause[(x + 1) % i];
		}
		x = -1;
		while (++x < i){
			pthread_create(&philo->list[x].th, NULL, &routin, &philo->list[x]);
		}
		pthread_create(&th[x],NULL,&checkdeath,philo->list);
		pthread_join(th[x],NULL);
		distroy(philo);
	}
	return 0;
}
