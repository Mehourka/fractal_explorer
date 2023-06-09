#include "bonus_fractol.h"
// #include <pthread.h>

// # define THREAD_COUNT 2
/*
#------------------------------------------------------------------------------#
#                                RANDOM                                        #
#------------------------------------------------------------------------------#
 */
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
/*
#------------------------------------------------------------------------------#
#                                  HOOKS                                       #
#------------------------------------------------------------------------------#
 */


void print_vector(double v[2])
{
	printf("(%f, %f)\n", v[0], v[1]);
}

typedef struct thread_data{
	t_data				*data;
	int					step_idx;
	int					step;
	pthread_mutex_t		*mutex;
}	t_thread_data;

// void thread_square_hook(void *param)
// {

// 	t_data			*data = param;
// 	t_thread_data	*th_data;
// 	pthread_t		thread[THREAD_COUNT];

// 	th_data = malloc(sizeof(t_thread_data));
// 	th_data->data = data;
// 	th_data->step_idx = -1;
// 	th_data->step = data->image->pixels[0] / THREAD_COUNT;
// 	pthread_mutex_init(th_data->mutex, NULL);

// 	for (int i = 0; i < THREAD_COUNT; i++)
// 	{
// 		pthread_create(&thread[i],)
// 	}

// 	pthread_mutex_destroy(th_data->mutex);

// }

void square_hook(void *param)
{

	t_data			*data = param;
	mlx_image_t		*image = data->image;
	double			*off = data->offset;
	double			pos[2];


	for (uint32_t i = 0; i < image->width; i++)
	{
		for(uint32_t j= 0; j < image->height; j++)
		{
			pos[0] = (double) i;
			pos[1] = (double) j;
			map_vector(pos, data);
			sub_vector(pos, off);
			if (pos[0] >= -1 && pos[0] <= 1 && pos[1] >= -1 && pos[1] <= 1)
				mlx_put_pixel(image, i, j, WHITE);
			else
				mlx_put_pixel(image, i, j, BLACK);
		}
	}
}



void circle_hook(void *param)
{

	t_data			*data = param;
	mlx_image_t		*image = data->image;
	double			*off = data->offset;
	double			pos[2];


	for (uint32_t i = 0; i < image->width; i++)
	{
		for(uint32_t j= 0; j < image->height; j++)
		{
			pos[0] = (double) i;
			pos[1] = (double) j;
			map_vector(pos, data);
			sub_vector(pos, off);
			if (pow(pos[0],2) + pow(pos[1], 2) < 1)
				mlx_put_pixel(image, i, j, WHITE);
			else
				mlx_put_pixel(image, i, j, BLACK);
		}
	}
}