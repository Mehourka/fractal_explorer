/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mlx_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:33:01 by kmehour           #+#    #+#             */
/*   Updated: 2023/06/14 12:33:11 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_fractol.h"

double	mod2(double v[2])
{
	return (v[0] * v[0] + v[1] * v[1]);
}

int	norm_rgba(float r, float g, float b, float a)
{
	r = fmin(fmax(r, 0), 1) * 255;
	g = fmin(fmax(g, 0), 1) * 255;
	b = fmin(fmax(b, 0), 1) * 255;
	a = fmin(fmax(a, 0), 1) * 255;
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | (int)a);
}

float	palette_function(float d, float t)
{
	return (0.5 + 0.5 * cos(M_PI * 2 * (1.0 * t + d)));
}

int	color_palette(float t)
{
	float	r;
	float	g;
	float	b;

	r = palette_function(-0.721, t);
	g = palette_function(-0.493, t);
	b = palette_function(-0.353, t);
	return (norm_rgba(r, g, b, 1));
}

void	render_pixel(mlx_image_t *img, int i, int j, double num_iter)
{
	t_data			*data;
	int				max_iter;
	int32_t			color;
	static double	shift;
	double			d;

	data = init_data();
	max_iter = data->max_iter;
	d = ft_map((double) num_iter, (double []){0, max_iter}, (double []){0, 1});
	shift += pow(10, -8.2);
	if (shift > 1)
		shift = 0;
	d = pow(d, 0.4);
	color = color_palette(d + shift);
	if (num_iter == max_iter)
		mlx_put_pixel(img, i, j, BLACK);
	else
		mlx_put_pixel(img, i, j, color);
}
