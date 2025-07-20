/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:26:26 by anpicard          #+#    #+#             */
/*   Updated: 2025/07/20 14:00:13 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	ft_isdigit(unsigned char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	valid_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][0] == '\0')
			return (0);
		else if (av[i][0] == '+')
			j++;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j++]))
				return (0);
		}
		if (ft_atoi(av[i]) == -1)
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac != 5 && ac != 6)
		return (printf("%s%s%s", RED, USAGE, RESET), 0);
	else if (!valid_args(ac, av))
		return (printf("%sInvalid Arguments\n%s", RED, RESET), 0);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (!init_table(ac, av, table))
	{
		free(table);
		return (1);
	}
	start_simulation(table);
	clean_up(table);
	return (0);
}
