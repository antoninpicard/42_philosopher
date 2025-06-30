/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:25:00 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/28 10:25:00 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	take_single_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->data->forks_mutex);
	while (philo->data->forks[fork_id] == 1)
	{
		pthread_mutex_unlock(&philo->data->forks_mutex);
		usleep(100);
		pthread_mutex_lock(&philo->data->forks_mutex);
	}
	philo->data->forks[fork_id] = 1;
	pthread_mutex_unlock(&philo->data->forks_mutex);
	print_mutex("%lld %d has taken a fork\n", philo);
}
