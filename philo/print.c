/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:02:23 by ketrevis          #+#    #+#             */
/*   Updated: 2024/01/24 11:55:07 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	print_state(t_philo *philo)
{
	char	*states[3];

	states[EATING] = "is eating";
	states[THINKING] = "is thinking";
	states[SLEEPING] = "is sleeping";
	pthread_mutex_lock(&philo->args->stdo_mutex);
	if (philo->args->stop)
	{
		pthread_mutex_unlock(&philo->args->stdo_mutex);
		return (0);
	}
	if (philo->state == EATING)
	{
		philo->last_eat = get_curr_time(philo);
		philo->eat_count += 1;
	}
	printf("%u %u %s\n", get_curr_time(philo) - philo->args->start_time,
		philo->id, states[philo->state]);
	pthread_mutex_unlock(&philo->args->stdo_mutex);
	return (1);
}

int	print_fork_pickup(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->stdo_mutex);
	if (philo->args->stop)
	{
		pthread_mutex_unlock(&philo->args->stdo_mutex);
		return (0);
	}
	printf("%u %u has taken a fork\n", get_curr_time(philo)
		- philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->stdo_mutex);
	return (1);
}
