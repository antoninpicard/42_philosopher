/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:07:30 by anpicard          #+#    #+#             */
/*   Updated: 2025/05/23 08:07:30 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>

# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_DIED "/sem_died"
# define SEM_MEAL "/sem_meal"
# define SEM_LAST_MEAL "/sem_last_meal"

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pid_t			pid;
	pthread_t		monitor_thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	long long		start_time;
	int				someone_died;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*died_sem;
	sem_t			*meal_sem;
	sem_t			*last_meal_sem;
	t_philo			*philos;
	pid_t			*pids;
}					t_data;

/* Initialization */
int					init_philosophers(t_data *data);
int					init_semaphores(t_data *data);

/* Process management */
int					fork_philos(t_data *data);
void				wait_philos(t_data *data);
void				kill_philos(t_data *data);

/* Philosopher routines */
void				philo_routine(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

/* Monitor functions */
void				*monitor_routine(void *arg);
int					is_died(t_philo *philo);
void				check_death(t_data *data);

/* Utility functions */
long long			timestamp(void);
void				print_sem(char *str, t_philo *philo);
void				my_sleep(time_t time, t_data *data);
int					ft_atoi(const char *str);
int					parse_args(int ac, char **av, t_data *data);

/* Cleanup */
void				cleanup_resources(t_data *data);
void				unlink_semaphores(void);

#endif
