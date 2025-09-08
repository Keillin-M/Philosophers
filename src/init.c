/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:16:06 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/05 12:22:10 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init(t_data *data)
{
	int	i;

	i = 0;
	data->end = 0;
	data->philo_array = malloc(sizeof(t_philo) * data->philos);
	if (!data->philo_array)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos);
	if (!data->forks)
		return (free(data->philo_array), 1);
	while (i < data->philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	while (i < data->philos)
	{
		data->philo_array[i].id = i + 1;
		data->philo_array[i].meal_count = 0;
		pthread_mutex_init(&data->philo_array[i].last_meal_lock, NULL);
		pthread_mutex_init(&data->philo_array[i].meal_count_lock, NULL);
		data->philo_array[i].data = data;
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->end_lock, NULL);
	return (0);
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->philos)
	{
		set_last_meal(&data->philo_array[i]);
		if (pthread_create(&data->philo_array[i].thread, NULL, 
				&routine, &data->philo_array[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor_death,
			(void *)data) != 0)
		return (1);
	if (data->must_eat)
	{
		if (pthread_create(&data->monitor_eat, NULL, monitor_eat_enough,
				(void *)data) != 0)
			return (1);
	}
	return (0);
}

int	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		if (pthread_join(data->philo_array[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
		return (1);
	if (data->must_eat)
	{
		if (pthread_join(data->monitor_eat, NULL))
			return (1);
	}
	return (0);
}
