/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:57:05 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/21 08:08:42 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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
