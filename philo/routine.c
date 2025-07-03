/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:59:57 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/28 10:23:28 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	take_forks(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = &philo->data->forks[philo->left_fork_id];
		second_fork = &philo->data->forks[philo->right_fork_id];
	}
	else
	{
		first_fork = &philo->data->forks[philo->right_fork_id];
		second_fork = &philo->data->forks[philo->left_fork_id];
	}
	take_single_fork(philo, first_fork);
	take_single_fork(philo, second_fork);
}

static void	release_forks(t_philo *philo)
{
	release_single_fork(&philo->data->forks[philo->left_fork_id]);
	release_single_fork(&philo->data->forks[philo->right_fork_id]);
}

static void	philo_eat(t_philo *philo)
{
	print_mutex("%lld %d is eating\n", philo);
	pthread_mutex_lock(&philo->last_meals);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->last_meals);
	my_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal);
}

static void	philo_think(t_philo *philo)
{
	time_t	time;

	pthread_mutex_lock(&philo->last_meals);
	time = (philo->data->time_to_die - (timestamp() - philo->last_meal)
			- philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->last_meals);
	if (time < 0)
		time = 0;
	if (time > 1000)
		time = 1000;
	print_mutex("%lld %d is thinking\n", philo);
	my_sleep(time, philo->data);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->start_time > timestamp())
		continue ;
	if (philo->data->nb_philo == 1)
	{
		print_mutex("%lld %d has taken a fork\n", philo);
		my_sleep(philo->data->time_to_die, philo->data);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		philo_think(philo);
	while (!is_died(philo))
	{
		take_forks(philo);
		philo_eat(philo);
		release_forks(philo);
		print_mutex("%lld %d is sleeping\n", philo);
		my_sleep(philo->data->time_to_sleep, philo->data);
		philo_think(philo);
	}
	return (NULL);
}
