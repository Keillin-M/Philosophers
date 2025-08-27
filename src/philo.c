/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:34:04 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/25 13:37:08 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (printf("Error: Wrong number of arguments\n"), 1);
	data->philos = parse_int(argv[1]);
	data->die = parse_int(argv[2]);
	data->eat = parse_int(argv[3]);
	data->sleep = parse_int(argv[4]);
	if (data->philos == -1 || data->die == -1 || data->eat == -1 
		|| data->sleep == -1)
		return (printf("Error: Invalid argument\n"), 1);
	if (argc == 6)
	{
		data->must_eat = parse_int(argv[5]);
		if (data->must_eat == -1)
			return (printf("Error: Invalid argument\n"), 1);
	}
	else
		data->must_eat = -1;
	return (0);
}

#include <sys/time.h>

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

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

void	*routine(void *data)
{
	t_philo	*philo;
	int	left_fork;
	int	right_fork;

	philo = (t_philo *)data;
	left_fork = philo->id - 1;
	right_fork = philo->id % philo->shared_data->philos;
	while (1)
	{
		if (left_fork < right_fork)
		{
			pthread_mutex_lock(&philo->shared_data->forks[left_fork]);
			pthread_mutex_lock(&philo->shared_data->forks[right_fork]);
		}
		else
		{
			pthread_mutex_lock(&philo->shared_data->forks[right_fork]);
			pthread_mutex_lock(&philo->shared_data->forks[left_fork]);
		}
		if (left_fork < right_fork)
		{
			pthread_mutex_unlock(&philo->shared_data->forks[left_fork]);
			pthread_mutex_unlock(&philo->shared_data->forks[right_fork]);
		}
		else
		{
			pthread_mutex_unlock(&philo->shared_data->forks[right_fork]);
			pthread_mutex_unlock(&philo->shared_data->forks[left_fork]);
		}
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	*data;
	t_philo	*philo;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	if (parse(argc, argv, &data))
		return (1);
	if (ft_init(philo, data))
		return (1);
	if (create_thread(data))
		return (1);
	if (join_thread(data))
		return (1);
	pthread_mutex_destroy(&mutex);
}
