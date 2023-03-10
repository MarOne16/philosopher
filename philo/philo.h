/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:10:10 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/10 23:01:04 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/time.h>

# define AC_BLACK "\x1b[30m"
# define AC_RED "\x1b[31m"
# define AC_GREEN "\x1b[32m"
# define AC_YELLOW "\x1b[33m"
# define AC_BLUE "\x1b[34m"
# define AC_MAGENTA "\x1b[35m"
# define AC_CYAN "\x1b[36m"
# define AC_WHITE "\x1b[37m"
# define AC_NORMAL "\x1b[m"

typedef struct s_philo
{
	pthread_t			th;
	int					id;
	size_t				kla;
	pthread_mutex_t		*print;
	pthread_mutex_t		left_f;
	pthread_mutex_t		*right_f;
	size_t				timedie;
	size_t				current_time;
	size_t				maxtime;
	size_t				timesleep;
	size_t				timeineat;
}						t_philo;

void		*routin(void *arg);
int			checkarg(char **argv);
void		runthread(t_philo *philo, int i);
void		feedthread(t_philo *philo, char **argv,
				pthread_mutex_t *print, size_t kla);
int			checkkla(t_philo *philo, int i);
size_t		ft_atoi(char *str);
void		putnbr(size_t nb);
void		printp(t_philo *philo, char *str, int x);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_sleepms(size_t ms, t_philo *philo);
size_t		get_time(void);

#endif /* PHILO_H */
