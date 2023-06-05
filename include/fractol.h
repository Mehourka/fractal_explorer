/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:21:34 by kmehour           #+#    #+#             */
/*   Updated: 2023/06/05 13:06:08 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "MLX42/MLX42.h"
# include <string.h>
# include <math.h>

# define WIDTH 300
# define HEIGHT 300
# define MAX_ITER 20

# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define COLOR 0xaa22ccFF
#define BPP sizeof(int32_t)

typedef struct data{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int32_t		max_iter;
	uint32_t		color;
	double		x_range[2];
	double		y_range[2];
	double		x_pix_range[2];
	double		y_pix_range[2];
	double		offset[2];
	double		pan_start[2];
}	t_data;


int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
t_data		*init_data();
void		ft_randomize(void* param);
void		ft_hook(void* param);
double		ft_map(double val, double in_range[2], double out_range[2]);
double		ft_abs(double a);

void		my_keyhook(mlx_key_data_t keydata, void* param);
void		my_scrollhook(double xdelta, double ydelta, void* param);
void		key_navigation(void *param);
void		scroll_zoom(double xdelta, double ydelta, void *param);
void		mouse_navigation(void *param);
void		resize_window(int32_t width, int32_t height, void *param);

void		square_hook(void *param);
void		circle_hook(void *param);

void		map_vector(double v[2], t_data *data);
void		add_vector(double v[2], double u[2]);
void		sub_vector(double v[2], double u[2]);
void		mult_vector(double v[2], double c);
void		cast_vector(double v[2], int u[2]);
void		print_vector(double v[2]);

void		iter_hook(void *param);
void		mandelbrot(void *param);
#endif