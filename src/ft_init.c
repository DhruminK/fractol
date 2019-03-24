/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 19:16:34 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/14 22:18:49 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_set			*ft_set_init(t_comp start, t_comp end, \
		t_point pstart, t_point pend)
{
	t_set		*set;

	if (!(set = (t_set*)malloc(sizeof(t_set))))
		return (0);
	set->c_start = start;
	set->c_end = end;
	set->p_start = pstart;
	set->p_end = pend;
	set->inc.real = (end.real - start.real) / (pend.x - pstart.x);
	set->inc.img = (end.img - start.img) / (pend.y - pstart.y);
	set->img = 0;
	return (set);
}

t_set			*ft_set(t_set set, int max_no, int curr_no)
{
	int			i;
	int			j;
	t_comp		div;
	t_set		*new_set;

	i = curr_no % max_no;
	j = curr_no / max_no;
	div.real = (set.c_end.real - set.c_start.real) / max_no;
	div.img = (set.c_end.img - set.c_start.img) / max_no;
	set.c_start.real = set.c_start.real + (div.real * i);
	set.c_start.img = set.c_start.img + (div.img * j);
	set.c_end.real = set.c_start.real + div.real;
	set.c_end.img = set.c_start.img + div.img;
	set.p_start.x = (set.p_end.x / max_no) * i;
	set.p_start.y = (set.p_end.y / max_no) * j;
	set.p_end.x = (set.p_end.x / max_no) * (i + 1);
	set.p_end.y = (set.p_end.y / max_no) * (j + 1);
	if (!(new_set = ft_set_init(set.c_start, set.c_end, \
					set.p_start, set.p_end)))
		return (0);
	new_set->img = set.img;
	new_set->is_julia = set.is_julia;
	new_set->c = set.c;
	new_set->n = set.n;
	return (new_set);
}
