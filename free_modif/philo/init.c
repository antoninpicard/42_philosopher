/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:56:59 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/30 10:38:00 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(int) * data->nb_philo);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		data->forks[i] = 0;
		i++;
	}
	if (pthread_mutex_init(&data->forks_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->died, NULL))
		return (0);
	return (1);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (0);
	if (!init_mutexes(data))
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork_id = i;
		data->philos[i].right_fork_id = (i + 1) % data->nb_philo;
		if (pthread_mutex_init(&data->philos[i].last_meals, NULL))
			return (0);
		if (pthread_mutex_init(&data->philos[i].meal, NULL))
			return (0);
		i++;
	}
	return (1);
}
