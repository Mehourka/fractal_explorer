/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mlx_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:39:44 by kmehour           #+#    #+#             */
/*   Updated: 2023/06/14 12:50:20 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_fractol.h"

int	is_valid_float(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
			i++;
		if (str[i] == '.' && !ft_strchr(str + i + 1, '.'))
			i++;
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

double	ft_atod(const char *num)
{
	double	signe;
	double	result;
	double	frac;

	signe = 1.0;
	result = 0;
	frac = 0.0;
	if (*num == '-')
	{
		signe *= -1.0;
		num++;
	}
	while (*num)
	{
		if (*num == '.')
		{
			frac = (num++ != 0);
		}
		result = result * 10 + (*num - '0');
		frac *= 0.1;
		num++;
	}
	if (frac == 0.0)
		frac = 1.0;
	return (signe * frac * result);
}

void	print_usage(void)
{
	ft_putstr_fd("Usage :\n\
		Mandelbrot  : ./fractol 1\n\
		Julia       : ./fractol 2 [re] [im]\n\
		Burnin Ship : ./fractol 3 \n",
		STDERR_FILENO);
}

void	select_fractal(uint32_t frac_choice, t_data *data)
{
	if (frac_choice < MANDELBROT || frac_choice > BURN_SHP)
	{
		print_usage();
		ft_error();
	}
	if (frac_choice == MANDELBROT)
		data->frac_function = &mandelbrot_pthread;
	else if (frac_choice == JULIA)
		data->frac_function = &julia_pthread;
	else if (frac_choice == BURN_SHP)
		data->frac_function = &burning_ship_pthread;
}

void	parse_arguments(int argc, char *argv[], t_data *data)
{
	uint32_t	frac_choice;

	if (argc != 2 && argc != 4)
	{
		print_usage();
		ft_error();
	}
	frac_choice = ft_atoi(argv[1]);
	select_fractal(frac_choice, data);
	if (argc == 4)
	{
		if (!is_valid_float(argv[2]) || !is_valid_float(argv[3]))
		{
			ft_putstr_fd("Invalid Julia parameters\n", STDERR_FILENO);
			ft_error();
		}
		data->julia_c[0] = ft_atod(argv[2]);
		data->julia_c[1] = ft_atod(argv[3]);
	}
}
