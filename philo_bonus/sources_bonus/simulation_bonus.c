/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:26:00 by anpicard          #+#    #+#             */
/*   Updated: 2025/07/20 14:26:00 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

static void	kill_all_processes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (table->philos[i].pid > 0)
			kill(table->philos[i].pid, SIGKILL);
		i++;
	}
}

static int	check_all_eaten(t_table *table)
{
	int	i;
	int	all_done;

	if (table->eat_count == -1)
		return (0);
	all_done = 1;
	i = 0;
	while (i < table->philo_count)
	{
		sem_wait(table->meal_check);
		if (table->philos[i].meals_counter < table->eat_count)
			all_done = 0;
		sem_post(table->meal_check);
		if (!all_done)
			break ;
		i++;
	}
	return (all_done);
}

static void	monitor_philosophers(t_table *table)
{
	int	status;
	int	finished;

	finished = 0;
	while (!finished)
	{
		if (waitpid(-1, &status, WNOHANG) > 0)
		{
			if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			{
				kill_all_processes(table);
				finished = 1;
			}
		}
		if (check_all_eaten(table))
		{
			table->stop = 1;
			kill_all_processes(table);
			finished = 1;
		}
		usleep(1000);
	}
}

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal = get_time_ms();
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		table->philos[i].pid = fork();
		if (table->philos[i].pid == 0)
			philo_routine(&table->philos[i]);
		else if (table->philos[i].pid < 0)
		{
			kill_all_processes(table);
			return ;
		}
		i++;
	}
	monitor_philosophers(table);
}

void	clean_up(t_table *table)
{
	if (table)
	{
		if (table->forks)
			sem_close(table->forks);
		if (table->write_lock)
			sem_close(table->write_lock);
		if (table->meal_check)
			sem_close(table->meal_check);
		free(table->philos);
		free(table);
	}
	sem_unlink("/forks");
	sem_unlink("/write_lock");
	sem_unlink("/meal_check");
}
