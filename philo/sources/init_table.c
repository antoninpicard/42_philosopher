/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:38:42 by anpicard          #+#    #+#             */
/*   Updated: 2025/07/20 15:05:57 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time_ms(void)
{
	long long		ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

static void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->phil_nbr)
		pthread_mutex_init(&table->forks[i], NULL);
	i = -1;
	while (++i < table->phil_nbr)
	{
		table->philos[i].table = table;
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (1 + i) % table->phil_nbr;
		table->philos[i].meal_counter = 0;
		table->philos[i].t_last_meal = get_time_ms();
	}
	pthread_mutex_init(&table->protect, NULL);
}

int	init_table(int ac, char **av, t_table *table)
{
	table->phil_nbr = ft_atoi(av[1]);
	table->tt_die = ft_atoi(av[2]);
	table->tt_eat = ft_atoi(av[3]);
	table->tt_sleep = ft_atoi(av[4]);
	table->sim_end = 0;
	table->eat_count = -1;
	if (ac == 6)
		table->eat_count = ft_atoi(av[5]);
	if (table->phil_nbr < 1 || table->phil_nbr > 200)
		return (printf("%sEnter Valid Philosophers Numbers%s\n",
				RED, RESET), 1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->phil_nbr);
	if (!table->forks)
		return (printf("Failed On Table Forks"), 1);
	table->philos = malloc(sizeof(t_philo) * table->phil_nbr);
	if (!table->philos)
	{
		free(table->forks);
		return (printf("Failed On Table Phils"), 1);
	}
	init_philos(table);
	return (0);
}
