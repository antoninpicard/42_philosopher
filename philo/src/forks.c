/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 08:18:02 by anpicard          #+#    #+#             */
/*   Updated: 2025/07/03 01:25:22 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	release_fork(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
}

void	take_fork(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
}
