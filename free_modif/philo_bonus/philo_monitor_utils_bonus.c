/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:10:30 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/27 08:22:09 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_died(t_philo *philo)
{
	int	result;

	sem_wait(philo->data->died_sem);
	result = philo->data->someone_died;
	sem_post(philo->data->died_sem);
	return (result);
}

void	philo_died(t_philo *philo)
{
	long long	current_time;

	current_time = timestamp() - philo->data->start_time;
	if (current_time < 0)
		current_time = 0;
	sem_wait(philo->data->died_sem);
	if (philo->data->someone_died == 0)
	{
		sem_wait(philo->data->print_sem);
		printf("%lld %d died\n", current_time, philo->id);
		sem_post(philo->data->print_sem);
		philo->data->someone_died = 1;
	}
	sem_post(philo->data->died_sem);
	exit(1);
}

int	all_philos_ate_enough(t_data *data)
{
	int	i;

	if (data->nb_meals <= 0)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten < data->nb_meals)
			return (0);
		i++;
	}
	return (1);
}
