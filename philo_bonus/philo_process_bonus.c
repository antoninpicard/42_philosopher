/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:05:30 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/27 08:05:30 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_last_meal_time(t_philo *philo)
{
	philo->last_meal = timestamp();
}

void	create_philo_process(t_data *data, int i)
{
	set_last_meal_time(&data->philos[i]);
	if (pthread_create(&data->philos[i].monitor_thread, NULL,
			monitor_routine, &data->philos[i]))
		exit(1);
	pthread_detach(data->philos[i].monitor_thread);
	philo_routine(&data->philos[i]);
	exit(0);
}
