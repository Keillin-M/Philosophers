/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:14:18 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/28 22:06:00 by kmaeda           ###   ########.fr       */
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

void	*monitor_death(void *data)
{
	t_data	*d;
	long	current_time;
	int	i;

	d = (t_data *)data;
	while (!d->end)
	{
		i = 0;
		while (i < d->philos)
		{
			current_time = get_time();
			if ((current_time - d->philo_array[i]->last_meal) > d->die)
			{
				print_status(&d->philo_array[i], "died");
				d->end = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (philo->data->end)
			break ;
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
