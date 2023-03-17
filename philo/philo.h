/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:10:10 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/17 13:17:07 by mqaos            ###   ########.fr       */
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
# include <math.h>
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

typedef struct mainphilo
{	
	int				max_philo;
	long long		maxtime;
	int				timeeat;
	int				timesleep;
	int				finish;
	long long		current_time;
	pthread_mutex_t	*forks;
	struct s_philo	*philo;
	pthread_mutex_t	kill;
	pthread_mutex_t	print;
}		t_mainphilo;

typedef struct s_philo
{
	struct mainphilo	*mainphilo;
	pthread_t			th;
	int					id;
	int					left_f;
	int					right_f;
	long long			timedie;
	long long			eat;
	pthread_mutex_t		time;
}						t_philo;

void		ft_eat(t_philo *philo);
int			checkeat(t_philo *philo);
void		printp(t_mainphilo *mainphilo, int id, char *msg, int x);
void		initmutex(t_mainphilo *philo, char **argv);
void		ft_sleepms(long long ms);
void		clear_all(t_mainphilo *mainphilo);
long long	gettime_ms(void);
long long	ft_atoi(char *str);
void		feedphilo(t_mainphilo *mainphilo, char **argv, long long eat);
void		feedthread(t_mainphilo *philo, char **argv);
int			lockphilo(t_mainphilo *mainphilo);
void		ft_sleep(t_philo *philo);
void		*routine(void *arg);
void		die_check(t_philo *philo);
void		*check_check(void *arg);
void		runthread(t_mainphilo *mainphilo);
int			checkarg(char **argv);
#endif /* PHILO_H */
