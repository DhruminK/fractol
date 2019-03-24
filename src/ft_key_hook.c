/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 23:20:03 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/22 17:49:03 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void		ft_translate(char dir, t_mlx *ml)
{
	int			hori;
	t_point		win;
	int			verti;

	hori = 0;
	verti = 0;
	win = ml->set->p_end;
	if (dir == 0b0001)
		hori = 1;
	else if (dir == 0b0010)
		hori = -1;
	else if (dir == 0b0100)
		verti = 1;
	else if (dir == 0b1000)
		verti = -1;
	ml->set->c_start.real += hori * ml->set->inc.real * TRANS_SCALE;
	ml->set->c_start.img += verti * ml->set->inc.img * TRANS_SCALE;
	ml->set->c_end.real += hori * ml->set->inc.real * TRANS_SCALE;
	ml->set->c_end.img += verti * ml->set->inc.img * TRANS_SCALE;
	if (!(ml->set->img = ft_create_img(ml, win.x, win.y)))
		ft_close(1);
	if (!(ft_thread(*(ml->set), NO_OF_THREADS)))
		ft_close(1);
	ft_add_img(ml, ml->set->img);
	ml->set->img = 0;
}

void		ft_change_n(int dir, t_mlx *ml)
{
	t_point		win;

	win = ml->set->p_end;
	if (!dir && ml->set->n == 2)
		return ;
	ml->set->n = ml->set->n + (dir ? 1 : -1);
	if (!(ml->set->img = ft_create_img(ml, win.x, win.y)))
		ft_close(1);
	if (!(ft_thread(*(ml->set), NO_OF_THREADS)))
		ft_close(1);
	ft_add_img(ml, ml->set->img);
	ml->set->img = 0;
}

int			key_press(int keycode, void *param)
{
	t_mlx		*ml;
	char		dir;

	ml = (t_mlx*)param;
	if (!ml || !ml->mlx)
		return (0);
	if (keycode == 53)
		ft_close(0);
	if (keycode == 124 || keycode == 123)
		dir = keycode == 123 ? 0b0010 : 0b0001;
	if (keycode == 126 || keycode == 125)
		dir = keycode == 126 ? 0b1000 : 0b0100;
	if ((keycode == 45 || keycode == 46) && (ml->set->n > 1))
		ft_change_n(keycode == 45, ml);
	if (keycode == 1)
		ml->mouse_move = ml->mouse_move ? 0 : 1;
	ft_translate(dir, ml);
	return (0);
}
