/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcingtools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:13:02 by mqaos             #+#    #+#             */
/*   Updated: 2023/02/27 19:59:38 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long	ft_atoi(char *str)
{
	long	x;
	long	z;
	long	i;

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

t_th	*lstnew(pthread_t th,long id,long status, long time,long timedie)
{
	t_th	*node;
	node = malloc(sizeof(t_th));
	if (!node)
		return(0);
	node->th = th;
	node->id = id;
	node->status = status;
	node->time = time;
	node->timedie = timedie;
	node->next = NULL;
	node->previous = NULL;
	return(node);
}

t_th	*ft_lstlast(t_th *lst)
{
	t_th	*l;

	if (!lst)
		return (0x0);
	l = lst;
	while (l -> next != 0)
		l = l -> next;
	return (l);
}

void	ft_lstadd_back(t_th **lst, t_th *new)
{
	t_th	*lst2;

	if (lst == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		lst2 = ft_lstlast(*lst);
		lst2 -> next = new;
		new -> previous = lst2;
	}
}