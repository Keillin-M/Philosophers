/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:16:06 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/28 15:16:37 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
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
		data->philo_array[i].last_meal = get_time();
		data->philo_array[i].shared_data = data;
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);
	data->start_time = get_time();
	return (0);
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		if (pthread_create(&data->philo_array[i].thread, NULL, 
				&routine, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		if (pthread_join(&data->philo_array[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
