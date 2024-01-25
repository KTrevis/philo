/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:17:09 by ketrevis          #+#    #+#             */
/*   Updated: 2024/01/25 10:14:47 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

static void	pickup_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->l_fork);
		print_fork_pickup(philo);
		pthread_mutex_lock(philo->r_fork);
		print_fork_pickup(philo);
		print_state(philo);
		usleep(philo->args->time_to_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_fork_pickup(philo);
		pthread_mutex_lock(&philo->l_fork);
		print_fork_pickup(philo);
		print_state(philo);
		usleep(philo->args->time_to_eat);
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

static void	eating(t_philo *philo)
{
	pickup_forks(philo);
	philo->state = SLEEPING;
}

static void	thinking(t_philo *philo)
{
	uint	time_until_death;

	print_state(philo);
	time_until_death = philo->args->time_to_die
		- (get_curr_time(philo) - philo->last_eat);
	while (time_until_death >= 100)
	{
		time_until_death = philo->args->time_to_die
			- (get_curr_time(philo) - philo->last_eat);
	}
	philo->state = EATING;
}

static void	sleeping(t_philo *philo)
{
	print_state(philo);
	usleep(philo->args->time_to_sleep);
	philo->state = THINKING;
}

void	*routine(void *arg)
{
	t_philo	*philo;
	void	(*f[3])(t_philo *philo);

	philo = arg;
	pthread_mutex_lock(&philo->args->routine_start);
	pthread_mutex_unlock(&philo->args->routine_start);
	f[THINKING] = thinking;
	f[EATING] = eating;
	f[SLEEPING] = sleeping;
	init_odd_philo(philo);
	if (philo->r_fork == NULL)
		return (arg);
	while (1)
	{
		pthread_mutex_lock(&philo->args->stdo_mutex);
		if (philo->args->stop)
			return (pthread_mutex_unlock(&philo->args->stdo_mutex), arg);
		pthread_mutex_unlock(&philo->args->stdo_mutex);
		f[philo->state](philo);
	}
	return (arg);
}
