/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:07:30 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/27 11:22:17 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_sem("%lld %d has taken a fork\n", philo);
	sem_wait(philo->data->forks);
	print_sem("%lld %d has taken a fork\n", philo);
	print_sem("%lld %d is eating\n", philo);
	sem_wait(philo->data->last_meal_sem);
	philo->last_meal = timestamp();
	sem_post(philo->data->last_meal_sem);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	my_sleep(philo->data->time_to_eat, philo->data);
	sem_wait(philo->data->meal_sem);
	philo->meals_eaten++;
	sem_post(philo->data->meal_sem);
}

void	philo_sleep(t_philo *philo)
{
	print_sem("%lld %d is sleeping\n", philo);
	my_sleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	time_t		time;
	long long	current_last_meal;

	sem_wait(philo->data->last_meal_sem);
	current_last_meal = philo->last_meal;
	sem_post(philo->data->last_meal_sem);
	time = (philo->data->time_to_die - (timestamp() - current_last_meal)
			- philo->data->time_to_eat) / 2;
	if (time < 0)
		time = 0;
	if (time > 1000)
		time = 1000;
	print_sem("%lld %d is thinking\n", philo);
	my_sleep(time, philo->data);
}

void	philo_routine(t_philo *philo)
{
	while (philo->data->start_time > timestamp())
		continue ;
	if (philo->data->nb_philo == 1)
	{
		print_sem("%lld %d has taken a fork\n", philo);
		while (1)
			usleep(1000);
	}
	if (philo->id % 2 == 0)
		philo_think(philo);
	while (1)
	{
		philo_eat(philo);
		if (philo->data->nb_meals > 0
			&& philo->meals_eaten >= philo->data->nb_meals)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
}
