/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:57:02 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/21 08:20:11 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_mutex(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_died(philo))
	{
		printf(str, timestamp() - philo->data->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

static void	set_last_meal_time(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].last_meals);
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->philos[i].last_meals);
		i++;
	}
}

int	launch_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	data->start_time = timestamp() + (data->nb_philo * 2 * 10);
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = 0;
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]))
			return (printf("Error: failed to create thread\n"), 0);
		i++;
	}
	set_last_meal_time(data);
	if (pthread_create(&monitor_thread, NULL, monitor, data))
		return (printf("Error: monitor thread failed\n"), 0);
	pthread_join(monitor_thread, NULL);
	return (1);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
