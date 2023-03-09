/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:01:04 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/09 22:49:25 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


size_t	maxtime;
size_t	timeeat;
size_t	timesleep;
int					ON = 1;

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

void	ft_eat(t_th *philo)
{
	philo->timedie = 0;
	// size_t t1 = get_time();
	printp(philo," is eat\n");
	ft_sleepms(philo->timeineat);
	// size_t t2 = get_time();
	
}
void	ft_sleep(t_th *philo)
{
	// size_t t1 = get_time();
	printp(philo," sleep\n");
	ft_sleepms(philo->timesleep);
	// size_t t2 = get_time();
}

void	*routin(void *arg)
{
	t_th	*philo = (t_th *)arg;
	if (philo->id  % 2)
		usleep(2);
	while (ON)
	{
		size_t t1 = get_time();
		pthread_mutex_lock(philo->left_f);
		pthread_mutex_lock(philo->right_f);
		size_t t2 = get_time();
		philo->current_time += t2 - t1;
		// philo->timedie += t2 - t1;
		printp(philo," taking a forks\n");
		size_t t3 = get_time();
		ft_eat(philo);
		size_t t4 = get_time();
		philo->current_time += t4 - t3;
		philo->timedie += t4 - t3;
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
		size_t t5 = get_time();
		if (philo->timedie < philo->maxtime)
			ft_sleep(philo);
		size_t t6 = get_time();
		philo->current_time += t6 - t5;
		philo->timedie += t6 - t5;
		if (philo->timedie < philo->maxtime)
			printp(philo," think\n");
		
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc == 5)
	{
		int i = ft_atoi(argv[1]);
		pthread_t	th[i];
		int x = -1;
		philo_t	*philo = malloc(sizeof(philo_t));
		philo->pause = malloc(sizeof(pthread_mutex_t)*i);
		philo->list = malloc(sizeof(t_th) * i);
		pthread_mutex_t	print;
		pthread_mutex_t	die;
		if(pthread_mutex_init(&print,NULL) 
		|| pthread_mutex_init(&die,NULL))
		{
			perror("Failed to init thread");
		}
		while (++x < i)
		{
			pthread_mutex_t	pa;
			if(pthread_mutex_init(&pa,NULL))
				perror("Failed to init thread");
			philo->pause[x] = pa;
			philo->print = &print;
			philo->die = &die;
			philo->list[x].print = &print;
			philo->list[x].die = &die;
			philo->list[x].kla = 0;
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
		// pthread_create(&th[x],NULL,&checkdeath,philo->list);
		// pthread_join(th[x],NULL);
		// distroy(philo);
		while (1)
		{
			x = -1;
			while (++x < i)
			{
				pthread_mutex_lock(philo->list[x].die);
				pthread_detach(philo->list[x].th);
				if (philo->list[x].timedie >= philo->list[x].maxtime || i <= 1)
				{
					pthread_mutex_lock(philo->print);
					printf("philo %d die\n",philo->list[x].id);
					ON = 0;
					return 0;
					pthread_mutex_unlock(philo->print);
					pthread_mutex_unlock(philo->list[x].die);
				}
				pthread_mutex_unlock(philo->list[x].die);
				// pthread_mutex_unlock(philo->print);
			}
		}
		
	}
	return 0;
}
