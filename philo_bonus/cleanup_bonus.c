/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:07:30 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/23 08:07:30 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_resources(t_data *data)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->print_sem)
		sem_close(data->print_sem);
	if (data->died_sem)
		sem_close(data->died_sem);
	if (data->meal_sem)
		sem_close(data->meal_sem);
	if (data->last_meal_sem)
		sem_close(data->last_meal_sem);
	unlink_semaphores();
	if (data->philos)
		free(data->philos);
	if (data->pids)
		free(data->pids);
}
