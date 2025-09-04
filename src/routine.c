/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:14:18 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/04 16:20:40 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_last_meal(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->last_meal_lock);
	time = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
	return (time);
}

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_lock);
}

int	get_meal_count(t_philo *philo)
{
	int	count;

	pthread_mutex_lock(&philo->meal_count_lock);
	count = philo->meal_count;
	pthread_mutex_unlock(&philo->meal_count_lock);
	return (count);
}

void	increase_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_count_lock);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_count_lock);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_end(philo->data))
			break ;
		pick_fork(philo);
		set_last_meal(philo);
		print_status(philo, "is eating");
		usleep(philo->data->eat * 1000);
		increase_meal(philo);
		drop_fork(philo);
		if (philo->data->must_eat > 0 
			&& get_meal_count(philo) >= philo->data->must_eat)
			break ;
		print_status(philo, "is sleeping");
		usleep(philo->data->sleep * 1000);
		print_status(philo, "is thinking");
		usleep(1000);
	}
	return (NULL);
}
