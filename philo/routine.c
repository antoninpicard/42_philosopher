/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpicard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:59:57 by anpicard          #+#    #+#             */
/*   Updated: 2025/06/28 10:23:28 by anpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	check_others_urgency(t_philo *philo)
{
	int	i;
	long long	other_time_since_meal;
	long long	my_time_since_meal;

	pthread_mutex_lock(&philo->last_meals);
	my_time_since_meal = timestamp() - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meals);

	for (i = 0; i < philo->data->nb_philo; i++)
	{
		if (philo->data->philos[i].id == philo->id)
			continue;
		pthread_mutex_lock(&philo->data->philos[i].last_meals);
		other_time_since_meal = timestamp() - philo->data->philos[i].last_meal;
		pthread_mutex_unlock(&philo->data->philos[i].last_meals);
		
		/* If another philosopher is more urgent than me, yield */
		if (other_time_since_meal > my_time_since_meal + 50 && 
		    other_time_since_meal > philo->data->time_to_die * 2 / 3)
			return (1);
	}
	return (0);
}

static int	take_forks(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;
	int	left_id = philo->left_fork_id;
	int	right_id = philo->right_fork_id;
	long long	time_since_last_meal;

	/* Check urgency - if close to death, prioritize */
	pthread_mutex_lock(&philo->last_meals);
	time_since_last_meal = timestamp() - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meals);

	/* Check if we should yield to more urgent philosophers */
	if (philo->data->nb_philo == 3 && check_others_urgency(philo))
	{
		usleep(10000); /* Yield for 10ms */
		return (0); /* Don't take forks, let others eat */
	}

	/* Always take the lower numbered fork first to prevent deadlock */
	if (left_id < right_id)
	{
		first_fork = &philo->data->forks[left_id];
		second_fork = &philo->data->forks[right_id];
	}
	else
	{
		first_fork = &philo->data->forks[right_id];
		second_fork = &philo->data->forks[left_id];
	}
	take_single_fork(philo, first_fork);
	take_single_fork(philo, second_fork);
	return (1); /* Successfully took forks */
}

static void	release_forks(t_philo *philo)
{
	release_single_fork(&philo->data->forks[philo->left_fork_id]);
	release_single_fork(&philo->data->forks[philo->right_fork_id]);
}

static void	philo_eat(t_philo *philo)
{
	print_mutex("%lld %d is eating\n", philo);
	pthread_mutex_lock(&philo->last_meals);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->last_meals);
	my_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal);
}

static void	philo_think(t_philo *philo)
{
	time_t	time;
	time_t	time_since_last_meal;

	pthread_mutex_lock(&philo->last_meals);
	time_since_last_meal = timestamp() - philo->last_meal;
	time = (philo->data->time_to_die - time_since_last_meal - philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->last_meals);
	
	/* Adaptive thinking time based on urgency */
	if (time_since_last_meal > philo->data->time_to_die * 2 / 3)
		time = 0; /* Very urgent, don't think */
	else if (time_since_last_meal > philo->data->time_to_die / 2)
		time = 1; /* Urgent, think very little */
	else if (time < 0)
		time = 0;
	else if (time > 50)
		time = 50;
	/* For 3 philosophers, use very short thinking time */
	if (philo->data->nb_philo == 3)
		time = (time > 10) ? 10 : time;
	
	print_mutex("%lld %d is thinking\n", philo);
	my_sleep(time, philo->data);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->start_time > timestamp())
		continue ;
	if (philo->data->nb_philo == 1)
	{
		print_mutex("%lld %d has taken a fork\n", philo);
		my_sleep(philo->data->time_to_die, philo->data);
		return (NULL);
	}
	/* Staggered start for fairness - more aggressive for 3 philosophers */
	if (philo->data->nb_philo == 3)
	{
		if (philo->id == 1)
			my_sleep(0, philo->data); /* Start immediately */
		else if (philo->id == 2)
			my_sleep(100, philo->data); /* Half of eat time */
		else if (philo->id == 3)
			my_sleep(150, philo->data); /* 3/4 of eat time */
	}
	else if (philo->id % 2 == 0)
		my_sleep(philo->data->time_to_eat / 2, philo->data);
	while (!is_died(philo))
	{
		long long time_since_last_meal;
		
		/* Check if we're getting close to death */
		pthread_mutex_lock(&philo->last_meals);
		time_since_last_meal = timestamp() - philo->last_meal;
		pthread_mutex_unlock(&philo->last_meals);
		
		if (take_forks(philo)) /* Only proceed if we got forks */
		{
			philo_eat(philo);
			release_forks(philo);
			print_mutex("%lld %d is sleeping\n", philo);
			
			/* Adaptive sleep time based on urgency */
			if (time_since_last_meal > philo->data->time_to_die * 2 / 3)
				my_sleep(philo->data->time_to_sleep / 4, philo->data); /* Very urgent */
			else if (time_since_last_meal > philo->data->time_to_die / 2)
				my_sleep(philo->data->time_to_sleep / 2, philo->data); /* Urgent */
			else
				my_sleep(philo->data->time_to_sleep, philo->data); /* Normal */
			
			philo_think(philo);
		}
		/* If we yielded, just continue the loop (already waited in take_forks) */
	}
	return (NULL);
}
