/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcingtools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:13:02 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/11 16:10:19 by mqaos            ###   ########.fr       */
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

void	printp(t_philo *philo, char *str, int x)
{
	pthread_mutex_lock(philo->print);
	if (x == 1)
		printf(AC_BLUE"%zu ms philo %d%s", philo->current_time, philo->id, str);
	else if (x == 2)
		printf(AC_YELLOW"%zu ms philo %d%s",
			philo->current_time, philo->id, str);
	else if (x == 3)
		printf(AC_WHITE"%zu ms philo %d%s",
			philo->current_time, philo->id, str);
	else
		printf(AC_MAGENTA"%zu ms philo %d%s",
			philo->current_time, philo->id, str);
	pthread_mutex_unlock(philo->print);
}

int	checkarg(char **argv)
{
	int	i;
	int	x;

	i = 0;
	if (ft_atoi(argv[1]) <= 0)
		return (1);
	while (argv[++i])
	{
		x = 0;
		while (argv[i][x])
		{
			if (argv[i][x] >= '0' && argv[i][x] <= '9')
				x++;
			else
				return (1);
		}
	}
	return (0);
}
