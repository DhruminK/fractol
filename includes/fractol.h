/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 18:40:25 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/22 17:48:17 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <sys/types.h>
# include <pthread.h>
# include <math.h>
# include "../libft/libft.h"
# include "mlx.h"
# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define MAX_ITERATIONS 255
# define NO_OF_THREADS 10
# define TRANS_SCALE 20
# define MAX_PT_CMP 100

typedef struct		s_comp
{
	double			real;
	double			img;
}					t_comp;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_img
{
	void			*img_ptr;
	int				*img_data;
	int				bpp;
	int				size_l;
	int				endian;
}					t_img;

typedef struct		s_set
{
	t_comp			c_start;
	t_comp			c_end;
	t_point			p_start;
	t_point			p_end;
	t_comp			inc;
	int				is_julia;
	t_comp			c;
	int				n;
	t_img			*img;
}					t_set;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	t_img			*img;
	t_set			*set;
	t_point			*mp;
	int				mouse_move;
}					t_mlx;

/*
** FUNCTIONS FOR MULTI-THREADING
*/
t_set				*ft_set_init(t_comp start, t_comp end, \
		t_point pstart, t_point pend);
t_set				*ft_set(t_set set, int max_no, int curr_no);
void				ft_pt_traverse(t_set set, t_img *img);
int					ft_thread(t_set set, int nt);
void				*ft_thread_run(void *arg);

/*
** FUNCTIONS FOR COLOR CONVERSION
*/
int					ft_color_conv(int r, int g, int b);
int					ft_color_conv_d(double r, double g, double b);

/*
** FUNCTIONS FOR COMPLEX NUMBER MANIPULATION
*/
void				ft_comp_mult(t_comp *res, t_comp a, t_comp b);
void				ft_comp_init(t_comp *c, double real, double img);
void				ft_comp_add(t_comp *res, t_comp a, t_comp b);
double				ft_comp_abssq(t_comp z);

/*
** FUNCTIONS FOR POINT MANIPULATION
*/
void				ft_ptinit(t_point *pt, int x, int y);
t_point				*ft_ptnew(int x, int y);
int					ft_ptcmp(t_point *p1, t_point *p2);
int					ft_ptabs(t_point p);

/*
** FUNCTIONS FOR MLX MANIPLUATION
*/
t_mlx				*ft_mlx_init(t_point win, t_comp start, t_comp end);
void				*ft_create_win(t_mlx *ml, int winx, int winy, char *name);
void				*ft_create_img(t_mlx *ml, int winx, int winy);
void				ft_add_img(t_mlx *ml, t_img *img);
int					ft_close(int err_no);

/*
** HOOK FUNCTIONS
*/
int					mouse_hook(int button, int x, int y, void *param);
int					mouse_move(int x, int y, void *param);
int					key_press(int keycode, void *param);

#endif
