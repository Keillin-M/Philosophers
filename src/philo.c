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
