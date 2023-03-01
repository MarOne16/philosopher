/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:01:04 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/01 17:22:13 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int r = 0;

pthread_mutex_t pthread;
pthread_mutex_t print;

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

void *thread_function(void *arg)
{
    printf("Hello from a new thread!\n");
    return NULL;
}

void ft_eat(t_th *t)
{
    int i =0;
    pthread_mutex_lock(&print);
    size_t t1 = get_time();
    printf("philo [%ld] is taking a forks\n",t->id);
    t->timedie = 0;
    if (t->next || t->previous)
    {
        if (t->next)
        {
            t->status = 0;
            t->next->status = 1;
        }
        if (t->previous)
        {
            t->status = 0;
            t->previous->status = 1;
        }
    }
    ft_sleepms(t->time);
    size_t t2 = get_time();
    t->timedie += t2 - t1;
    if (t->timedie > t->maxtime)
    {
        printf("x_x philo [%ld] die",t->id);
        exit(0);
    }

    pthread_mutex_unlock(&print);
}
void ft_sleep(t_th *t)
{
    int i =0;
    pthread_mutex_lock(&print);
    size_t t1 = get_time();
    printf("philo [%ld] in sleep mode...\n",t->id);
    size_t t2 = get_time();
    t->timedie += t2 - t1;
    if (t->timedie > t->maxtime)
    {
        printf("x_x philo [%ld] die",t->id);
        exit(0);
    }
    printf("[%ldms] philo [%ld] out sleep mode...\n",t->timedie,t->id);
    pthread_mutex_unlock(&print);
}
void ft_think(t_th *t)
{
    pthread_mutex_lock(&print);
    int i =0;
    size_t t1 = get_time();;
    printf("philo [%ld] in think mode...\n",t->id);
    pthread_mutex_unlock(&print);
    ft_sleepms(t->time);
    size_t t2 = get_time();
    t->timedie += t2 - t1;
    if (t->timedie > t->maxtime)
    {
        printf("x_x philo [%ld] die",t->id);
        exit(0);
    }
    printf("[%ldms] philo [%ld] out think mode...\n",t->timedie,t->id);
    pthread_mutex_unlock(&print);
}

void* handel(void *th)
{
    t_th    *t = (t_th*)th;
    while (1)
    {
        if (t->status == 1)
            ft_eat(t);
        else
        {
            ft_sleep(t);
            ft_think(t);
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc == 5)
    {
        pthread_mutex_init(&pthread, NULL);
        pthread_mutex_init(&print, NULL);
        long total = ft_atoi(argv[1]);
        t_th *t = NULL;
        t_th *t2 = NULL;
        pthread_t th[total];
        long i = -1;
        int x;
        while (++i < total)
        {
            x = ((i + 1) % 2);
            ft_lstadd_back(&t,lstnew(th[i],i,x,ft_atoi(argv[2]),ft_atoi(argv[3]),ft_atoi(argv[4])));
        }
        i = 0;
        while (t)
        {
            pthread_create(&th[i],NULL,&handel,(void*)t);
            t = t->next;
            i++;
        }
        i = -1;
        while (++i < ft_atoi(argv[1]))
            pthread_join(th[i],NULL);
    }
    else
        printf("Error\n");
    return 0;
}
