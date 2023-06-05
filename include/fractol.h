/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:21:34 by kmehour           #+#    #+#             */
/*   Updated: 2023/05/29 16:40:50 by kmehour          ###   ########.fr       */
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

# define WIDTH 512
# define HEIGHT 512
# define MAX_ITER 20

# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
#define BPP sizeof(int32_t)

typedef struct data{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			max_iter;
	float		x_range[2];
	float		y_range[2];
	float		x_pix_range[2];
	float		y_pix_range[2];
	float		offset[2];
	float		pan_start[2];
}	t_data;

int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
t_data		*init_data();
void		my_scrollhook(double xdelta, double ydelta, void* param);
void		my_keyhook(mlx_key_data_t keydata, void* param);
void		ft_randomize(void* param);
void		ft_hook(void* param);
float		ft_map(float val, float in_range[2], float out_range[2]);
float		ft_abs(float a);
void		key_navigation(void *param);
void		scroll_zoom(double xdelta, double ydelta, void *param);
// void		mandelbrot(void *param);
void		map_vector(float v[2], t_data *data);
void		add_vector(float v[2], float u[2]);
void		mul_vector(float v[2], float c);
void		print_vector(float v[2]);
void		square_hook(void *param);
void		mouse_navigation(void *param);
// void iter_hook(void *param);
#endif