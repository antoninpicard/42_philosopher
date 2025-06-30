/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:19:39 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/30 10:37:00 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	long long		start_time;
	int				someone_died;
	int				*forks;
	pthread_mutex_t	forks_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	died;
	struct s_philo	*philos;
}					t_data;

typedef struct s_fork
{
	int				taken;
	pthread_mutex_t	lock;
}			t_fork;


typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	last_meals;
	pthread_mutex_t	meal;
	int				left_fork_id;
	t_fork			*left_fork;
	int				right_fork_id;
	t_fork			*right_fork;
	t_data			*data;
}					t_philo;

/* Initialization */
int					init_philosophers(t_data *data);

/* Thread management */
int					launch_threads(t_data *data);
void				join_threads(t_data *data);

/* Philosopher routines */
void				*philo_routine(void *arg);
void				action(t_philo *philo);

/* Fork utilities */
void				take_single_fork(t_philo *philo, int fork_id);

/* Monitor functions */
void				*monitor(void *arg);
int					is_died(t_philo *philo);
int					check_death_status(t_data *data);
int					all_philos_ate_enough(t_data *data);

/* Utility functions */
long long			timestamp(void);
void				print_mutex(char *str, t_philo *philo);
void				my_sleep(time_t time, t_data *data);
int					ft_atoi(const char *str);

/* Cleanup */
void				cleanup_resources(t_data *data);

#endif
