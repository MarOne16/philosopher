/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:10:10 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/09 19:24:38 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PHILO_H)
#define PHILO_H
#include    <string.h>
#include    <unistd.h>
#include    <pthread.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <errno.h>
#include    <sys/time.h>

typedef struct s_th
{
	pthread_t           th;
	int                 id;
	int                 kla;
	pthread_mutex_t		*print;
	pthread_mutex_t		*die;
	pthread_mutex_t		*left_f;
	pthread_mutex_t		*right_f;
	size_t              timedie;
	size_t				current_time;
	size_t				maxtime;
	size_t				timesleep;
	size_t				timeineat;
	int					off;
	
}t_th;

struct philo_t
{
	t_th            *list;
	pthread_mutex_t		*print;
	pthread_mutex_t		*die;
	pthread_mutex_t *pause;
	
}typedef philo_t;

t_th	*lstnew(pthread_t th,int id,int status,size_t timedie);
void	ft_lstadd_front(t_th **lst, t_th *new);
t_th	*ft_lstlast(t_th *lst);
void	ft_lstadd_back(t_th **lst, t_th *new);
void	ft_putstr_fd(char *s, int fd);
void    *handel(void *th);
size_t	ft_atoi(char *str);
void	putnbr(size_t nb);
void	printp(t_th *philo,char *str);
void	distroy(philo_t *philo);

#endif // PHILO_H
