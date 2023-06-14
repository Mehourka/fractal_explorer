/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:11:46 by kmehour           #+#    #+#             */
/*   Updated: 2023/06/14 13:12:50 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_abs(double a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

double	ft_map(double val, double in_range[2], double out_range[2])
{
	double	scale;
	double	mapped_value;

	scale = (val - in_range[0]) / (in_range[1] - in_range[0]);
	mapped_value = (out_range[0] + (out_range[1] - out_range[0]) * scale);
	return (mapped_value);
}
