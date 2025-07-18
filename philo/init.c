/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:56:59 by anpicard          #+#    #+#             */
/*   Updated: 2025/07/18 10:51:28 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		data->forks[i].id = i;
		if (pthread_mutex_init(&data->forks[i].mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i].mutex);
			free(data->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	int	i;

	if (!init_forks(data))
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->forks[i].mutex);
			i++;
		}
		free(data->forks);
		return (0);
	}
	if (pthread_mutex_init(&data->died, NULL))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->forks[i].mutex);
			i++;
		}
		free(data->forks);
		pthread_mutex_destroy(&data->print_mutex);
		return (0);
	}
	return (1);
}

static void	cleanup_init_failure(t_data *data, int philo_index)
{
	int	j;
	j = 0;
	while (j < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[j].mutex);
		j++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->died);
	j = 0;
	while (j < philo_index)
	{
		pthread_mutex_destroy(&data->philos[j].last_meals);
		pthread_mutex_destroy(&data->philos[j].meal);
		j++;
	}
	free(data->forks);
	free(data->philos);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (0);
	if (!init_mutexes(data)){
		if (data->forks)
			free(data->forks);
		free(data->philos);
		return (0);
	}
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
		{
			cleanup_init_failure(data, i);
			return (0);
		}
		if (pthread_mutex_init(&data->philos[i].meal, NULL))
		{
			pthread_mutex_destroy(&data->philos[i].last_meals);
			cleanup_init_failure(data, i);
			return (0);
		}
		i++;
	}
	return (1);
}
