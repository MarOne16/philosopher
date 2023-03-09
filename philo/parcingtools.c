/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcingtools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:13:02 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/09 20:17:28 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

size_t	ft_atoi(char *str)
{
	size_t	x;
	size_t	z;
	size_t	i;

	x = 1;
	z = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			x *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		z *= 10;
		z += str[i] - '0';
		i++;
	}
	return (z * x);
}

void	printp(t_th *philo,char *str)
{
	pthread_mutex_lock(philo->print);
	printf("%zu ms philo %d%s",philo->current_time,philo->id,str);
	pthread_mutex_unlock(philo->print);	
}

void	distroy(philo_t *philo)
{
	int x;

	x = -1;
	while (&philo->list[++x])
	{
		pthread_mutex_destroy(philo->list[x].left_f);
		free(&philo->list[++x]);
	}
	pthread_mutex_destroy(philo->print);
}