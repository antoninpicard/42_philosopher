/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 07:50:52 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/29 17:46:59 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	percise_sleep(philo, philo->table->tt_sleep, 1);
}

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
	usleep(100);
}
