/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 20:05:06 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/22 17:44:48 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			ft_thread_cancel(pthread_t **pid, int i)
{
	while (i >= 0)
	{
		if (*pid[i])
			pthread_cancel((*pid)[i]);
		i = i - 1;
	}
	free(*pid);
	return (0);
}

int			ft_thread_join(pthread_t **pid, int n)
{
	int		i;

	i = -1;
	while (++i < n)
		pthread_join((*pid)[i], 0);
	free(*pid);
	return (1);
}

int			ft_thread(t_set set, int nt)
{
	t_set			*new_set;
	pthread_t		*pid;
	int				i;

	if (!(pid = (pthread_t*)malloc(sizeof(pthread_t) * (nt * nt))))
		return (0);
	i = 0;
	while (i < nt * nt)
	{
		if (!(new_set = ft_set(set, nt, i)))
			return (ft_thread_cancel(&pid, i));
		if (pthread_create(pid + i, 0, ft_thread_run, new_set))
			return (ft_thread_cancel(&pid, i));
		i = i + 1;
	}
	return (ft_thread_join(&pid, nt * nt));
}
