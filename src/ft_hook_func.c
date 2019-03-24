/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:28:43 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/22 17:48:01 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			ft_zoom(t_mlx *ml, int zoom, t_point pt)
{
	t_comp			ori;
	t_point			win;

	win = ml->set->p_end;
	ori.real = ml->set->c_start.real + (ml->set->inc.real * pt.x);
	ori.img = ml->set->c_start.img + (ml->set->inc.img * pt.y);
	ml->set->inc.real = ml->set->inc.real * (zoom ? 0.5 : 2.0);
	ml->set->inc.img = ml->set->inc.img * (zoom ? 0.5 : 2.0);
	ml->set->c_start.real = ori.real - (ml->set->inc.real * pt.x);
	ml->set->c_start.img = ori.img - (ml->set->inc.img * pt.y);
	ml->set->c_end.real = ml->set->c_start.real + (ml->set->inc.real * win.x);
	ml->set->c_end.img = ml->set->c_start.img + (ml->set->inc.img * win.y);
	if (!(ml->set->img = ft_create_img(ml, win.x, win.y)))
		ft_close(1);
	if (!(ft_thread(*(ml->set), NO_OF_THREADS)))
		ft_close(1);
	ft_add_img(ml, ml->set->img);
	ml->set->img = 0;
	return (0);
}

int			mouse_hook(int button, int x, int y, void *param)
{
	t_mlx		*ml;
	t_point		pt;

	ml = (t_mlx*)param;
	if (!ml || !ml->mlx)
		return (ft_close(1));
	ft_ptinit(&pt, x, y);
	if ((button == 4 || button == 2) \
			&& ft_comp_abssq(ml->set->inc) < 0.000025)
		ft_zoom(ml, 0, pt);
	else if ((button == 5 || button == 1) \
			&& ft_comp_abssq(ml->set->inc) > 2.5e-30)
		ft_zoom(ml, 1, pt);
	return (0);
}

void		ft_form_set(t_mlx *ml, t_point p)
{
	t_point		win;

	win = ml->set->p_end;
	ml->set->c.real = ml->set->c_start.real + (ml->set->inc.real * p.x);
	ml->set->c.img = ml->set->c_start.img + (ml->set->inc.img * p.y);
	if (!(ml->set->img = ft_create_img(ml, win.x, win.y)))
		ft_close(1);
	if (!(ft_thread(*(ml->set), NO_OF_THREADS)))
		ft_close(1);
	ft_add_img(ml, ml->set->img);
	ml->set->img = 0;
}

int			mouse_move(int x, int y, void *param)
{
	t_mlx		*ml;
	t_point		test;

	ml = (t_mlx*)param;
	if (!ml || !ml->mlx)
		return (ft_close(1));
	if (!ml->set->is_julia || !ml->mouse_move)
		return (0);
	if (!ml->mp)
		ml->mp = ft_ptnew(x, y);
	else
	{
		ft_ptinit(&test, x, y);
		if (!ft_ptcmp(ml->mp, &test))
			return (0);
		free(ml->mp);
		ml->mp = ft_ptnew(x, y);
	}
	ft_form_set(ml, *(ml->mp));
	return (0);
}
