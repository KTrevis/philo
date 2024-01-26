/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:23:45 by ketrevis          #+#    #+#             */
/*   Updated: 2024/01/26 11:56:15 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	get_curr_time(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(&philo->args->time_mutex);
	gettimeofday(&tv, NULL);
	pthread_mutex_unlock(&philo->args->time_mutex);
	return (((tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

void	init_odd_philo(t_philo *philo)
{
	if (philo->id % 2)
	{
		philo->state = THINKING;
		print_state(philo);
		usleep(philo->args->time_to_eat);
		philo->state = EATING;
	}
}
