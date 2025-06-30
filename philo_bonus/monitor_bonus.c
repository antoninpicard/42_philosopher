/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:07:30 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/27 10:18:27 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int			is_died(t_philo *philo);
void		philo_died(t_philo *philo);
int			all_philos_ate_enough(t_data *data);

void	*monitor_routine(void *arg)
{
	t_philo		*philo;
	long long	current_last_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->last_meal_sem);
		current_last_meal = philo->last_meal;
		sem_post(philo->data->last_meal_sem);
		if ((timestamp() - current_last_meal) > philo->data->time_to_die)
			philo_died(philo);
		sem_wait(philo->data->meal_sem);
		if (philo->data->nb_meals > 0
			&& philo->meals_eaten >= philo->data->nb_meals)
		{
			sem_post(philo->data->meal_sem);
			break ;
		}
		sem_post(philo->data->meal_sem);
		usleep(1000);
	}
	return (NULL);
}

static int	process_waitpid_result(t_data *data, int status, int *philos_done)
{
	if (WEXITSTATUS(status) == 1)
	{
		kill_philos(data);
		return (1);
	}
	else if (data->nb_meals > 0)
	{
		(*philos_done)++;
		if (*philos_done >= data->nb_philo)
			return (1);
	}
	return (0);
}

void	check_death(t_data *data)
{
	int	status;
	int	philos_done;

	philos_done = 0;
	while (1)
	{
		if (waitpid(-1, &status, WNOHANG) > 0)
		{
			if (process_waitpid_result(data, status, &philos_done))
				return ;
		}
		if (data->nb_meals > 0 && all_philos_ate_enough(data))
		{
			kill_philos(data);
			return ;
		}
		usleep(1000);
	}
}
