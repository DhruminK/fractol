/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 19:02:44 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/22 17:48:32 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_mlx		*ft_mlx_init(t_point win, t_comp start, t_comp end)
{
	t_mlx			*ml;
	t_point			pstart;

	if (!(ml = (t_mlx*)malloc(sizeof(t_mlx))))
		return (0);
	ft_ptinit(&pstart, 0, 0);
	if (!(ml->set = ft_set_init(start, end, pstart, win)))
		return (0);
	if (!(ml->mlx = mlx_init()))
		return (0);
	ml->win = 0;
	ml->mp = 0;
	ml->img = 0;
	ml->mouse_move = 1;
	return (ml);
}

void		*ft_create_win(t_mlx *ml, int winx, int winy, char *name)
{
	if (ml && ml->mlx)
		return (mlx_new_window(ml->mlx, winx, winy, name));
	return (0);
}

void		*ft_create_img(t_mlx *ml, int winx, int winy)
{
	t_img		*img;

	if (!ml || !ml->mlx || !(img = (t_img*)malloc(sizeof(t_img))))
		return (0);
	if (!(img->img_ptr = mlx_new_image(ml->mlx, winx, winy)))
		return (0);
	if (!(img->img_data = (int*)mlx_get_data_addr(img->img_ptr, \
					&(img->bpp), &(img->size_l), &(img->endian))))
		return (0);
	return (img);
}

void		ft_add_img(t_mlx *ml, t_img *img)
{
	if (!ml || !ml->mlx)
		return ;
	if (ml->img)
	{
		mlx_destroy_image(ml->mlx, ml->img->img_ptr);
		free(ml->img);
	}
	if (ml->win && img)
	{
		mlx_put_image_to_window(ml->mlx, ml->win, img->img_ptr, 0, 0);
		ml->img = img;
	}
}
