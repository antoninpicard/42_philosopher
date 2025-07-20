/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:05:04 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/30 00:49:43 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

int	ft_atoi(char *arg)
{
	int					i;
	unsigned long long	r;

	i = 0;
	r = 0;
	if (arg[i] == '+')
	{
		if (!arg[1])
			return (-1);
		i++;
	}
	while (arg[i])
	{
		r = r * 10 + arg[i] - 48;
		if (r > INT_MAX)
			return (-1);
		i++;
	}
	return (r);
}
