/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:34:04 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/02 18:07:50 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_data *data)
{
	data->start_time = get_time();
	printf("%ld Philo 1 has taken a fork\n", get_time() - data->start_time);
	usleep(data->die * 1000);
	printf("%ld Philo 1 has died\n", get_time() - data->start_time);
	return (0);
}

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
	if (data.must_eat != -1)
	{
		if (data.must_eat == 1)
			printf("All philosophers have eaten at least %d time\n", 
				data.must_eat);
		else
			printf("All philosophers have eaten at least %d times\n", 
				data.must_eat);
	}
	ft_clean(&data);
	return (0);
}
