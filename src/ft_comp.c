/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 18:42:41 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/14 23:01:16 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			ft_comp_init(t_comp *c, double real, double img)
{
	if (!c)
		return ;
	c->real = real;
	c->img = img;
}

void			ft_comp_mult(t_comp *res, t_comp a, t_comp b)
{
	t_comp		tmp;

	if (!res)
		return ;
	tmp.real = (a.real * b.real) - (a.img * b.img);
	tmp.img = (a.real * b.img) + (a.img * b.real);
	*res = tmp;
}

void			ft_comp_add(t_comp *res, t_comp a, t_comp b)
{
	t_comp		tmp;

	if (!res)
		return ;
	tmp.real = (a.real + b.real);
	tmp.img = (a.img + b.img);
	*res = tmp;
}

double			ft_comp_abssq(t_comp z)
{
	return ((z.real * z.real) + (z.img * z.img));
}
