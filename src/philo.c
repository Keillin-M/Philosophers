/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:34:04 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/05 11:48:27 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->end_lock);
	result = data->end;
	pthread_mutex_unlock(&data->end_lock);
	return (result);
}

void	set_end(t_data *data)
{
	pthread_mutex_lock(&data->end_lock);
	data->end = 1;
	pthread_mutex_unlock(&data->end_lock);
}

static int	one_philo(t_data *data)
{
	data->start_time = get_time();
	printf("%ld 1 has taken a fork\n", get_time() - data->start_time);
	usleep(data->die * 1000);
	printf("%ld 1 has died\n", get_time() - data->start_time);
	return (0);
}

static int	parse(int argc, char **argv, t_data *data)
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
		if (argv[5][0] - '0' == 0 && argv[5][1] == '\0')
			data->must_eat = 0;
		else
			data->must_eat = parse_int(argv[5]);
		if (data->must_eat == -1)
			return (printf("Error: Invalid argument\n"), 1);
	}
	else
		data->must_eat = -1;
	if (data->philos == 1)
		one_philo(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse(argc, argv, &data))
		return (1);
	if (data.philos == 1)
		return (0);
	if (ft_init(&data))
		return (1);
	if (create_thread(&data))
		return (1);
	if (join_thread(&data))
		return (1);
	ft_clean(&data);
	return (0);
}
