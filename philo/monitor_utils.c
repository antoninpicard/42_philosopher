/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:09:00 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/28 11:09:00 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_status(t_data *data)
{
	int	died;

	pthread_mutex_lock(&data->died);
	died = data->someone_died;
	pthread_mutex_unlock(&data->died);
	return (died);
}

int	all_philos_ate_enough(t_data *data)
{
	int	i;
	int	meals_count;

	if (data->nb_meals <= 0)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal);
		meals_count = data->philos[i].meals_eaten;
		pthread_mutex_unlock(&data->philos[i].meal);
		if (meals_count < data->nb_meals)
			return (0);
		i++;
	}
	return (1);
}
