/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:07:30 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/30 11:15:28 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DIED);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_LAST_MEAL);
}

int	init_semaphores(t_data *data)
{
	unlink_semaphores();
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->nb_philo);
	if (data->forks == SEM_FAILED)
		return (0);
	data->print_sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (0);
	data->died_sem = sem_open(SEM_DIED, O_CREAT, 0644, 1);
	if (data->died_sem == SEM_FAILED)
		return (0);
	data->meal_sem = sem_open(SEM_MEAL, O_CREAT, 0644, 1);
	if (data->meal_sem == SEM_FAILED)
		return (0);
	data->last_meal_sem = sem_open(SEM_LAST_MEAL, O_CREAT, 0644, 1);
	if (data->last_meal_sem == SEM_FAILED)
		return (0);
	return (1);
}

int	init_philosophers(t_data *data)
{
	int	i;

	if (!init_semaphores(data))
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (0);
	data->pids = malloc(sizeof(pid_t) * data->nb_philo);
	if (!data->pids)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].pid = -1;
		i++;
	}
	return (1);
}
