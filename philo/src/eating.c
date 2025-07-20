/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:52:35 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/29 17:47:11 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->protect);
	philo->t_last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->table->protect);
	print_status(philo, "is eating");
	percise_sleep(philo, philo->table->tt_eat, 1);
	pthread_mutex_lock(&philo->table->protect);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->table->protect);
}
