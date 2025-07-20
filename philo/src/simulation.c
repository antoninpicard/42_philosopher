/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:22:43 by anpicard          #+#    #+#             */
/*   Updated: 2025/07/08 07:57:03 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	percise_sleep(philo, philo->table->tt_die, 0);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->phil_nbr == 1)
		return (one_philo(arg));
	pthread_mutex_lock(&philo->table->protect);
	philo->t_last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->table->protect);
	if (philo->id % 2 == 0)
		percise_sleep(philo, philo->table->tt_sleep, 1);
	while (!check_death(philo->table))
	{
		take_fork(philo);
		eating(philo);
		release_fork(philo);
		if (philo->table->eat_count != -1
			&& philo->meal_counter >= philo->table->eat_count)
			break ;
		thinking(philo);
		percise_sleep(philo, philo->table->tt_sleep, 1);
	}
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time_ms();
	i = -1;
	while (++i < table->phil_nbr)
	{
		pthread_create(&table->philos[i].thread,
			NULL, routine, &table->philos[i]);
	}
	monitor(table);
	i = -1;
	while (++i < table->phil_nbr)
		pthread_join(table->philos[i].thread, NULL);
}
