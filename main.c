/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 19:22:12 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/14 23:51:57 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int		ft_puterror(int err_no)
{
	if (!(err_no))
	{
		ft_putendl("Usage: fractol [fractals]");
		ft_putendl("Fractals :\n-->Mandelbrot\n-->Julia");
		ft_putendl("-->Generalized Mandelbrot");
	}
	else
		ft_putendl("Error");
	return (1);
}

int		ft_close(int err_no)
{
	if (err_no)
	{
		ft_puterror(1);
		exit(1);
	}
	else
		exit(0);
}

void	ft_hook_func(t_mlx *ml)
{
	if (!ml->win)
		return ;
	mlx_mouse_hook(ml->win, mouse_hook, ml);
	mlx_hook(ml->win, 6, 0, mouse_move, ml);
	mlx_hook(ml->win, 17, 0, ft_close, 0);
	mlx_hook(ml->win, 2, 0, key_press, ml);
	mlx_loop(ml);
}

int		ft_mlx(int is_julia, int n)
{
	t_comp			start;
	t_comp			end;
	t_point			win;
	t_mlx			*ml;

	ft_comp_init(&start, -2.0, 2.0);
	ft_comp_init(&end, 2.0, -2.0);
	ft_ptinit(&win, WIN_WIDTH, WIN_HEIGHT);
	if (!(ml = ft_mlx_init(win, start, end)))
		return (ft_puterror(1));
	ml->set->is_julia = is_julia;
	ml->set->n = n;
	ft_comp_init(&start, -1, 0);
	ml->set->c = start;
	if (!(ml->set->img = ft_create_img(ml, WIN_WIDTH, WIN_HEIGHT)))
		return (ft_puterror(1));
	if (!(ft_thread(*(ml->set), 20)))
		return (ft_puterror(1));
	if (!(ml->win = ft_create_win(ml, WIN_WIDTH, WIN_HEIGHT, "FRACTOL")))
		return (ft_puterror(1));
	ft_add_img(ml, ml->set->img);
	ml->set->img = 0;
	ft_hook_func(ml);
	return (0);
}

int		main(int ac, char **av)
{
	int		is_julia;
	int		n;

	if (ac != 2 || (ft_strcmp("Mandelbrot", av[1]) \
				&& ft_strcmp("Julia", av[1]) \
				&& ft_strcmp("Generalized Mandelbrot", av[1])))
		return (ft_puterror(0));
	is_julia = !ft_strcmp("Julia", av[1]);
	n = ft_strcmp("Generalized Mandelbrot", av[1]) ? 1 : 2;
	return (ft_mlx(is_julia, n));
}
