/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fractol.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:21:34 by kmehour           #+#    #+#             */
/*   Updated: 2023/06/14 13:56:04 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_FRACTOL_H
# define BONUS_FRACTOL_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <math.h>
# include <pthread.h>

# define MANDELBROT 1
# define JULIA 2
# define BURN_SHP 3

# define WIDTH 512  //512512
# define HEIGHT 512 //512512
# define MAX_ITER 50
# define N_THREADS 64

# define BLACK 0x161616FF
# ifndef M_PI
#  define M_PI 3.14159265358979323846 /* pi */
# endif

# define TRUE 1
# define FALSE 0

typedef struct data
{
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
}				t_data;

// Utils
t_data			*init_data(void);
void			free_data(void);
void			ft_error(void);
double			ft_map(double val, double in_range[2], double out_range[2]);
double			ft_atod(const char *str);
void			parse_arguments(int argc, char *argv[], t_data *data);

// Hooks
void			keyboard_hooks(void *param);
void			mouse_hooks(void *param);
void			julia_mouse_control(double xpos, double ypos, void *param);

// Vectors
void			map_vector(double v[2], t_data *data);
void			add_vector(double v[2], double u[2]);
void			sub_vector(double v[2], double u[2]);
void			mult_vector(double v[2], double c);
void			cast_vector(double v[2], int u[2]);
double			mod2(double v[2]);

void			mandelbrot_pthread(void *param);
void			julia_pthread(void *param);
void			burning_ship_pthread(void *param);
void			set_interval(uint32_t limits[2], t_data *data);

void			render_pixel(mlx_image_t *img, int i, int j, double num_iter);

#endif