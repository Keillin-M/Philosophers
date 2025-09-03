/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:14:18 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/03 14:48:29 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_eat_enough(void *data)
{
	int		i;
	int		all_full;
	t_data	*d;

	d = (t_data *)data;
	while (!d->end && d->must_eat > 0)
	{
		all_full = 1;
		i = -1;
		while (++i < d->philos)
		{
			if (d->philo_array[i].meal_count < d->must_eat)
			{
				all_full = 0;
				break ;
			}
		}
		if (all_full)
		{
			d->end = 1;
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_death(void *data)
{
	int		i;
	long	current_time;
	t_data	*d;

	d = (t_data *)data;
	while (!d->end)
	{
		i = 0;
		while (i < d->philos)
		{
			current_time = get_time();
			if ((current_time - d->philo_array[i].last_meal) >= d->die)
			{
				print_status(&d->philo_array[i], "died");
				d->end = 1;
				return (NULL);
			}
			i++;
		}
		usleep(10);
	}
	return (NULL);
}

void	pick_fork(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philos;
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		print_status(philo, "has taken a fork");
	}
}

void	drop_fork(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philos;
	if (philo->id % 2 != 0)
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
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (philo->data->end)
			break ;
		pick_fork(philo);
		philo->last_meal = get_time();
		print_status(philo, "is eating");
		usleep(philo->data->eat * 1000);
		philo->meal_count++;
		drop_fork(philo);
		if (philo->data->must_eat > 0 
			&& philo->meal_count >= philo->data->must_eat)
			break ;
		print_status(philo, "is sleeping");
		usleep(philo->data->sleep * 1000);
		print_status(philo, "is thinking");
		usleep(1000);
	}
	return (NULL);
}
