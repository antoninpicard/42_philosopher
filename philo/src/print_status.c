/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:54:49 by anpicard          #+#    #+#             */
/*   Updated: 2025/07/02 16:16:16 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->table->protect);
	if (!philo->table->sim_end)
	{
		time = get_time_ms() - philo->table->start_time;
		printf("%lld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->protect);
}
