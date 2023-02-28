/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:01:04 by mqaos             #+#    #+#             */
/*   Updated: 2023/02/28 19:16:35 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int r = 0;

pthread_mutex_t pthread;
pthread_mutex_t print;

void ft_eat(t_th *t)
{
    int i =0;
    struct timeval tp;
    struct timeval tp2;
    pthread_mutex_lock(&print);
    gettimeofday(&tp,NULL);
    printf("philo [%ld] is taking a forks\n",t->id);
    if (t->next && t->previous)
    {
        t->status = 0;
        t->previous->status = 1;
        t->next->status = 1;
    }
    else
        t->status = 0;
    usleep(t->time);
    gettimeofday(&tp2,NULL);
    t->timedie += (tp2.tv_usec - tp.tv_usec);
    // write(1, "philo out eat mode...\n", 23);
    printf("[%ldms] philo [%ld] out eat mode...\n",t->timedie / 1000,t->id);
    pthread_mutex_unlock(&print);
}
void ft_sleep(t_th *t)
{
    int i =0;
    struct timeval tp;
    struct timeval tp2;
    pthread_mutex_lock(&print);
    gettimeofday(&tp,NULL);
    printf("philo [%ld] in sleep mode...\n",t->id);
    usleep(t->time);
    gettimeofday(&tp2,NULL);
    t->timedie -= (tp2.tv_usec - tp.tv_usec);
    printf("[%ldms] philo [%ld] out sleep mode...\n",t->timedie / 1000,t->id);
    pthread_mutex_unlock(&print);
}
void ft_think(t_th *t)
{
    pthread_mutex_lock(&print);
    int i =0;
    struct timeval tp;
    struct timeval tp2;
    gettimeofday(&tp,NULL);
    printf("philo [%ld] in think mode...\n",t->id);
    pthread_mutex_unlock(&print);
    usleep(t->time);
    gettimeofday(&tp2,NULL);
    t->timedie -= (tp2.tv_usec - tp.tv_usec);
    printf("[%ldms] philo [%ld] out think mode...\n",t->timedie  / 1000,t->id);
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
        pthread_mutex_lock(&print);
        if (t->timedie <= 0)
        {
            printf("philo [%ld] die",t->id);
            exit(0);
        }
        pthread_mutex_unlock(&print);
        // pthread_mutex_unlock(&pthread);
        // pthread_mutex_lock(&pthread);
        // pthread_mutex_unlock(&pthread);
        // pthread_mutex_lock(&pthread);
        // pthread_mutex_unlock(&pthread);
        // pthread_mutex_unlock(&pthread);
    }
    // printf("thread number %d\n",t->id);
    // free(th);
    return NULL;
}



int main(int argc, char *argv[])
{
    if (argc == 4)
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
            x = (i % 2);
            ft_lstadd_back(&t,lstnew(th[i],i,x,ft_atoi(argv[2]),ft_atoi(argv[3])));
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
