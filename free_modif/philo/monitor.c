/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:45:03 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/28 11:11:00 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int	is_died(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo->data->died);
	result = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->died);
	return (result);
}

static void	*if_died(t_data *data, int i)
{
	pthread_mutex_lock(&data->died);
	if (data->someone_died == 0)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d died\n", timestamp() - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		data->someone_died = 1;
	}
	pthread_mutex_unlock(&data->died);
	return (NULL);
}

static int	check_philosopher_death(t_data *data, int i)
{
	long long	current_last_meal;

	pthread_mutex_lock(&data->philos[i].last_meals);
	current_last_meal = data->philos[i].last_meal;
	pthread_mutex_unlock(&data->philos[i].last_meals);
	if ((timestamp() - current_last_meal) > data->time_to_die)
	{
		if_died(data, i);
		return (1);
	}
	return (0);
}

static int	check_all_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (check_death_status(data))
			return (1);
		if (check_philosopher_death(data, i))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death_status(data))
			break ;
		if (check_all_philosophers(data))
			break ;
		if (all_philos_ate_enough(data))
		{
			pthread_mutex_lock(&data->died);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->died);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
