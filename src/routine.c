/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:14:18 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/28 15:14:40 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_fork(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philos;
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->forks[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		pthread_mutex_lock(&philo->data->forks[left_fork]);
	}
}

void	drop_fork(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philos;
	if (left_fork < right_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
	}
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pick_fork(philo);
		print_status(philo, "is eating");
		philo->last_meal = get_time();
		usleep(philo->data->eat * 1000);
		philo->meal_count++;
		drop_fork(philo);
		print_status(philo, "is sleeping");
		usleep(philo->data->sleep * 1000);
		print_status(philo, "is thinking");
		if (philo->data->must_eat != -1 && philo->meal_count >= philo->data->must_eat)
			break ;
	}
	return (NULL);
}
