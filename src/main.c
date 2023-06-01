#include "fractol.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include <string.h>
#define WIDTH 720
#define HEIGHT 480

#define BPP sizeof(int32_t)

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// static void ft_hook(void* param)
// {
// 	const mlx_t*	mlx = param;

// 	printf("WIDTH %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }

void my_scrollhook(double xdelta, double ydelta, void* param)
{
	(void) param;
	if (ydelta > 0)
		puts("Up!");
	else if (ydelta < 0)
		puts("Down!");

	if (xdelta > 0)
		puts("Slide left!");
	else if (xdelta < 0)
		puts("Slide right!");

}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	(void) param;
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		puts("Hello ");

	// If we RELEASE the 'K' key, print "World".
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		puts("World");

	// If we HOLD the 'L' key, print "!".
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
		puts("!");
}

int main(void)
{

	// mlx_set_setting(MLX_MAXIMIZED, true);

	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		ft_error();

	// Drawing using mlx_image_t
	// mlx_image_t* img = mlx_new_image(mlx, 300, 300);
	// if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	// 	ft_error();
	// memset(img->pixels,0xFF,  img->width * img->height * BPP);

	// Draw using put_pixel
	// for(int i = 99; i < 200; i++)
	// {
	// 	for(int j = 90; j < 200; j++)
	// 		mlx_put_pixel(img, i, j, i<<8 | j << 16| 255);
	// }




	// mlx_loop_hook(mlx, ft_hook, mlx);
	// mlx_scroll_hook(mlx, &my_scrollhook, NULL);
	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}