/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:26:00 by anpicard          #+#    #+#             */
/*   Updated: 2025/07/20 14:26:00 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	print_status_bonus(t_philo *philo, char *status)
{
	sem_wait(philo->table->write_lock);
	if (!philo->table->stop)
	{
		printf("%lld %d %s\n", get_time_ms() - philo->table->start_time,
			philo->id, status);
	}
	sem_post(philo->table->write_lock);
}

void	precise_sleep_bonus(int time)
{
	long long	start_time;

	start_time = get_time_ms();
	while (get_time_ms() - start_time < time)
		usleep(100);
}

int	should_stop(t_philo *philo)
{
	sem_wait(philo->table->meal_check);
	if (philo->table->stop)
	{
		sem_post(philo->table->meal_check);
		return (1);
	}
	if (get_time_ms() - philo->last_meal > philo->table->tt_die)
	{
		philo->table->stop = 1;
		sem_post(philo->table->meal_check);
		sem_wait(philo->table->write_lock);
		printf("%lld %d died\n", get_time_ms() - philo->table->start_time,
			philo->id);
		exit(1);
	}
	sem_post(philo->table->meal_check);
	return (0);
}

void	eat_bonus(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_status_bonus(philo, "has taken a fork");
	sem_wait(philo->table->forks);
	print_status_bonus(philo, "has taken a fork");
	print_status_bonus(philo, "is eating");
	sem_wait(philo->table->meal_check);
	philo->last_meal = get_time_ms();
	philo->meals_counter++;
	sem_post(philo->table->meal_check);
	precise_sleep_bonus(philo->table->tt_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_sleep_bonus(philo->table->tt_eat / 2);
	while (!should_stop(philo))
	{
		eat_bonus(philo);
		if (philo->table->eat_count != -1
			&& philo->meals_counter >= philo->table->eat_count)
			break ;
		print_status_bonus(philo, "is sleeping");
		precise_sleep_bonus(philo->table->tt_sleep);
		print_status_bonus(philo, "is thinking");
		usleep(100);
	}
	exit(0);
}
