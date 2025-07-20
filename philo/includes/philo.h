/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:44:58 by anpicard          #+#    #+#             */
/*   Updated: 2025/07/02 16:06:56 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>

# define RED "\e[31m"
# define GREEN "\033[32m"
# define RESET "\e[0m"
# define USAGE "Usage: ./philo <nbr_philo> <time_to_die> <time_to_eat> \
<time_to_sleep> [eat_count]\n"

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	protect;
	struct s_philo	*philos;
	long long		start_time;
	int				phil_nbr;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				eat_count;
	int				sim_end;
}			t_table;

typedef struct s_philo
{
	pthread_t	thread;
	t_table		*table;
	long long	t_last_meal;
	int			id;
	int			left_fork;
	int			right_fork;
	int			meal_counter;
}				t_philo;

int			ft_atoi(char *arg);
int			init_table(int ac, char **av, t_table *table);
void		start_simulation(t_table *table);
void		thinking(t_philo *philo);
void		take_fork(t_philo *philo);
void		release_fork(t_philo *philo);
void		print_status(t_philo *philo, char *status);
long long	get_time_ms(void);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
int			is_died(t_philo *philo);
int			check_death(t_table *table);
void		monitor(t_table *table);
void		percise_sleep(t_philo *philo, int time, int flag);

#endif
