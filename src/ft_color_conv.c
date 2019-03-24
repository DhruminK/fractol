/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 19:37:31 by dkhatri           #+#    #+#             */
/*   Updated: 2019/03/14 19:42:39 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			ft_color_conv(int r, int g, int b)
{
	r = r > 255 ? 255 : r;
	r = r < 0 ? 0 : r;
	g = g > 255 ? 255 : g;
	g = g < 0 ? 0 : g;
	b = b > 255 ? 255 : b;
	b = b < 0 ? 0 : b;
	return (r << 16 | g << 8 | b);
}

int			ft_color_conv_d(double r, double g, double b)
{
	int			res;
	int			i;

	r = r > 1.0 ? 1 : r;
	r = r < 0 ? 0 : r;
	g = g > 1 ? 1 : g;
	g = g < 0 ? 0 : g;
	b = b > 1 ? 1 : b;
	b = b < 0 ? 0 : b;
	i = (int)floor(r * 255);
	res = i << 16;
	i = (int)floor(g * 255);
	res = res | i << 8;
	i = (int)floor(b * 255);
	res = res | i;
	return (res);
}
