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

#ifndef BONUS_FRACTOL_H
# define BONUS_FRACTOL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "MLX42/MLX42.h"
# include <string.h>
# include <math.h>
# include <pthread.h>

# define MANDELBROT	1
# define JULIA		2
# define BURN_SHP	3

# define WIDTH 512//512512
# define HEIGHT 512//512512
# define MAX_ITER 50
# define N_THREADS 100

# define WHITE 0xFFFFFFFF
# define BLACK 0x161616FF
# define COLOR 0x00FFFFFF
# define M_PI 3.14159265358979323846  /* pi */

#define TRUE 1
#define FALSE 0

# define FRAC_JULIA 1
# define FRAC_MANDL 2
# define BPP sizeof(int32_t)
# define min(x, y) x < y ? x : y

typedef struct data{
	mlx_t		*mlx;
	mlx_image_t	*image;
	void		*frac_function;
	uint32_t	max_iter;
	uint32_t	color;
	double		x_range[2];
	double		y_range[2];
	double		x_pix_range[2];
	double		y_pix_range[2];
	double		julia_c[2];
	double		offset[2];
	double		pan_start[2];
	double		t;
	double		step_i;
}	t_data;


void		ft_error(void);
t_data		*init_data(void);
void		free_data(void);
double		ft_map(double val, double in_range[2], double out_range[2]);

			// Hooks
void		keyboard_hooks(void *param);
void		mouse_hooks(void *param);
void		julia_mouse_control(double xpos, double ypos, void* param);

void		map_vector(double v[2], t_data *data);
void		add_vector(double v[2], double u[2]);
void		sub_vector(double v[2], double u[2]);
void		mult_vector(double v[2], double c);
void		cast_vector(double v[2], int u[2]);
double		mod2(double v[2]);
int			get_rgba(int r, int g, int b, int a);
void		render_pixel(mlx_image_t *img, int i, int j, double num_iter);

void		mandelbrot_pthread(void *param);
void		julia_pthread(void *param);
void		burning_ship_pthread(void *param);

double		ft_atod(const char *str);
int			parse_arguments(int argc, char *argv[], t_data *data);


#endif