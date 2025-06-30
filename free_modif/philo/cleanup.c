/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:30:00 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/21 09:30:00 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	cleanup_resources(t_data *data)
{
	int	i;

	if (data->forks)
	{
		free(data->forks);
	}
	pthread_mutex_destroy(&data->forks_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->died);
	if (data->philos)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->philos[i].last_meals);
			pthread_mutex_destroy(&data->philos[i].meal);
			i++;
		}
		free(data->philos);
	}
}
