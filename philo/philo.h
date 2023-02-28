/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:10:10 by mqaos             #+#    #+#             */
/*   Updated: 2023/02/27 20:00:15 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PHILO_H)
#define PHILO_H
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/time.h>

typedef struct s_th
{
    pthread_t           th;
    long                id;
    long                status;
    long                time;
    long                timedie;
    struct s_th         *next;
    struct s_th         *previous;
    
}t_th;

struct philo_t
{
    pthread_mutex_t paus;
    int             i;
}typedef philo_t ;
t_th	*lstnew(pthread_t th,long id,long status, long time,long timedie);
t_th	*ft_lstlast(t_th *lst);
void	ft_lstadd_back(t_th **lst, t_th *new);
void	ft_putstr_fd(char *s, int fd);
void* handel(void *th);
long	ft_atoi(char *str);

#endif // PHILO_H
