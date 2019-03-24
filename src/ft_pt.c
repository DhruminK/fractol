/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:59:50 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/14 23:14:23 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_point			*ft_ptnew(int x, int y)
{
	t_point		*pt;

	if (!(pt = (t_point*)malloc(sizeof(t_point))))
		return (0);
	pt->x = x;
	pt->y = y;
	return (pt);
}

void			ft_ptinit(t_point *pt, int x, int y)
{
	if (!pt)
		return ;
	pt->x = x;
	pt->y = y;
}

int				ft_ptabs(t_point p)
{
	return ((p.x * p.x) + (p.y * p.y));
}

int				ft_ptcmp(t_point *p1, t_point *p2)
{
	t_point		p;

	p.x = p2->x - p1->x;
	p.y = p2->y - p1->y;
	if (ft_ptabs(p) < MAX_PT_CMP)
		return (0);
	return (1);
}
