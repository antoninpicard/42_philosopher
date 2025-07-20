/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:29:42 by anpicard          #+#    #+#             */
/*   Updated: 2025/07/20 15:09:28 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>
# include <limits.h>

# define RED "\e[31m"
# define RESET "\e[0m"
# define USAGE "Usage: ./philo_bonus <nbr_philo> <time_to_die> <time_to_eat> \
<time_to_sleep> [eat_count]\n"

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	long			last_meal;
	int				meals_counter;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int			philo_count;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			eat_count;
	long long	start_time;
	int			stop;
	t_philo		*philos;
	sem_t		*forks;
	sem_t		*write_lock;
	sem_t		*meal_check;
}			t_table;

/* Function prototypes */
int			ft_atoi(char *arg);
long long	get_time_ms(void);
int			init_table(int ac, char **av, t_table *table);
void		start_simulation(t_table *table);
void		clean_up(t_table *table);
void		philo_routine(t_philo *philo);
void		print_status_bonus(t_philo *philo, char *status);
void		precise_sleep_bonus(int time);
int			should_stop(t_philo *philo);
void		eat_bonus(t_philo *philo);

#endif
