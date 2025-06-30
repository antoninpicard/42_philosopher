/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:07:30 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/27 08:21:37 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_sem(char *str, t_philo *philo)
{
	long long	current_time;

	current_time = timestamp() - philo->data->start_time;
	if (current_time < 0)
		current_time = 0;
	sem_wait(philo->data->print_sem);
	if (!is_died(philo))
		printf(str, current_time, philo->id);
	sem_post(philo->data->print_sem);
}

void	my_sleep(time_t time, t_data *data)
{
	time_t	wait;

	wait = timestamp() + time;
	while (timestamp() < wait)
	{
		if (is_died(data->philos))
			break ;
		usleep(100);
	}
}
