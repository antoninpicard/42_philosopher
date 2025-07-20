/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:55:14 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/30 16:56:08 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	init_table(int ac, char **av, t_table *table)
{
	table->philo_count = ft_atoi(av[1]);
	table->tt_die = ft_atoi(av[2]);
	table->tt_eat = ft_atoi(av[3]);
	table->tt_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->eat_count = ft_atoi(av[5]);
	else
		table->eat_count = -1;
	table->start_time = get_time_ms();
	table->stop = 0;
	sem_unlink("/forks");
	sem_unlink("/write_lock");
	sem_unlink("/meal_check");
	table->forks = sem_open("/forks", O_CREAT, 0644, table->philo_count);
	table->write_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	table->meal_check = sem_open("/meal_check", O_CREAT, 0644, 1);
	if (table->forks == SEM_FAILED || table->write_lock == SEM_FAILED
		|| table->meal_check == SEM_FAILED)
		return (0);
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (0);
	return (1);
}
