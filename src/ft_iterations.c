/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 18:48:42 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/14 22:19:51 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			ft_iterations(t_comp init, t_comp c, int n, int mi)
{
	t_comp		res;
	double		d;
	int			i;
	int			j;

	res = init;
	i = -1;
	d = exp((-1) * ft_comp_abssq(res));
	while (++i < mi && (j = -1))
	{
		if (ft_comp_abssq(res) > 4)
			break ;
		while (++j < n)
			ft_comp_mult(&res, res, res);
		ft_comp_add(&res, res, c);
		if (res.real == init.real && res.img == init.img && (i = mi))
			break ;
		d += exp((-1) * ft_comp_abssq(res));
	}
	if (i == mi)
		return (0);
	if (i < mi / 2)
		return (ft_color_conv_d((1 - d / 200), 1 - (d / 200 + 0.5), d / 200));
	return (ft_color_conv_d(0.5, 0.5 - (1 - d / 200), 1 - d / 200));
}

void		ft_pt_traverse(t_set set, t_img *img)
{
	t_point			pt;
	t_comp			c;
	t_comp			zero;

	pt = set.p_start;
	c = set.c_start;
	zero.real = 0;
	zero.img = 0;
	while (pt.y < set.p_end.y)
	{
		pt.x = set.p_start.x;
		c.real = set.c_start.real;
		while (pt.x < set.p_end.x)
		{
			img->img_data[(int)floor((pt.y * img->size_l / 4) + pt.x)\
			] = ft_iterations(set.is_julia ? c : zero, \
					set.is_julia ? set.c : c, set.n, MAX_ITERATIONS);
			pt.x = pt.x + 1;
			c.real = c.real + set.inc.real;
		}
		pt.y = pt.y + 1;
		c.img = c.img + set.inc.img;
	}
}

void		*ft_thread_run(void *arg)
{
	t_set		*set;

	if (!arg)
		return (0);
	set = (t_set*)arg;
	ft_pt_traverse(*set, set->img);
	free(set);
	return (0);
}
