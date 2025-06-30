/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:07:30 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/27 08:15:30 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_philo_process(t_data *data, int i);

int	fork_philos(t_data *data)
{
	int		i;
	pid_t	pid;

	data->start_time = timestamp();
	i = 0;
	while (i < data->nb_philo)
	{
		pid = fork();
		if (pid < 0)
			return (0);
		else if (pid == 0)
			create_philo_process(data, i);
		else
			data->pids[i] = pid;
		i++;
	}
	return (1);
}

void	wait_philos(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}

void	kill_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->pids[i] > 0)
			kill(data->pids[i], SIGKILL);
		i++;
	}
}
