#include "fractol.h"

int is_valid_float(const char *str)
{
	int i;

	i = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if(i == 0 && str[i] == '-')
			i++;
		if(str[i] == '.' && !ft_strchr(str + i + 1, '.'))
			i++;
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

double ft_atod(const char *num)
{
	double	whole;
	double	frac;
	double	dec;

	whole = ft_atoi(num);
	frac = 0.0;
	dec = 0.0;
	while(*num)
	{
		if (*num == '.')
		{
			frac = 1.0;
			num++;
		}
		frac *= 0.1;
		dec += (*num - '0') * frac;
		num++;
	}
	if (frac == 0.0)
		frac = 1.0;
	if(whole < 0)
		dec *= -1;
	return (whole + dec);
}

void print_usage(void)
{
	ft_putstr_fd("Usage :\n\
		 Mandelbrot  : ./fractol 1\n\
		 Julia       : ./fractol 2 [re] [im]\n\
		 Burnin Ship : ./fractol 3 \n"
		 , STDERR_FILENO);
}
int parse_arguments(int argc, char *argv[], t_data *data)
{

	uint32_t frac_choice;

	if (argc != 2 && argc != 4)
	{
		print_usage();
		ft_error();
	}

	frac_choice = ft_atoi(argv[1]);
	if (frac_choice < MANDELBROT || frac_choice > BURN_SHP)
	{
		print_usage();
		ft_error();
	}

	if (argc == 4)
	{
		if(!is_valid_float(argv[2]) || !is_valid_float(argv[3]))
		{
			ft_putstr_fd("Invalid Julia parameters\n", STDERR_FILENO);
			ft_error();
		}
		data->julia_c[0] = ft_atod(argv[2]);
		data->julia_c[1] = ft_atod(argv[3]);

		printf("Arguments (%f, %f)\n", data->julia_c[0], data->julia_c[1]);

	}


	if (frac_choice == MANDELBROT)
		data->frac_function = &mandelbrot;
	else if (frac_choice == JULIA)
		data->frac_function = &julia;
	else if (frac_choice == BURN_SHP)
		data->frac_function = &burning_ship;


	(void) argv;
	return 0;
}
