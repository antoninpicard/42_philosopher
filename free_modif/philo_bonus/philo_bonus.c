/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:07:30 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/23 08:07:30 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_overflow(char *str)
{
	if (ft_atoi(str) > 2147483647 || ft_atoi(str) < -2147483647)
		return (0);
	return (1);
}

int	is_digit_string(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int ac, char **av, t_data *data)
{
	if (!is_digit_string(av[1]) || !is_digit_string(av[2])
		|| !is_digit_string(av[3]) || !is_digit_string(av[4]) || (ac == 6
			&& !is_digit_string(av[5])) || !check_overflow(av[1])
		|| !check_overflow(av[2]) || !check_overflow(av[3])
		|| !check_overflow(av[4]) || (ac == 6 && !check_overflow(av[5])))
		return (0);
	if (ft_atoi(av[1]) == 0)
		return (0);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->someone_died = 0;
	data->start_time = 0;
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = -1;
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	unlink_semaphores();
	if (ac != 5 && ac != 6)
	{
		printf("Usage:%s nb_philo ", av[0]);
		printf("time_to_die time_to_eat time_to_sleep [nb_meals]\n");
		return (1);
	}
	if (!parse_args(ac, av, &data))
		return (printf("Error: invalid arguments\n"), 1);
	if (!init_philosophers(&data))
		return (printf("Error during initialization\n"), 1);
	if (!fork_philos(&data))
	{
		printf("Error launching processes\n");
		cleanup_resources(&data);
		return (1);
	}
	check_death(&data);
	wait_philos(&data);
	cleanup_resources(&data);
	return (0);
}
