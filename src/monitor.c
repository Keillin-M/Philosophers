/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:11:40 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/04 16:05:11 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_eat_enough(void *data)
{
	int		i;
	int		all_full;
	t_data	*d;

	d = (t_data *)data;
	while (!check_end(data) && d->must_eat > 0)
	{
		all_full = 1;
		i = -1;
		while (++i < d->philos)
		{
			if (get_meal_count(&d->philo_array[i]) < d->must_eat)
			{
				all_full = 0;
				break ;
			}
		}
		if (all_full)
		{
			set_end(data);
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
	while (!check_end(data))
	{
		i = 0;
		while (i < d->philos)
		{
			current_time = get_time();
			if ((current_time - get_last_meal(&d->philo_array[i])) >= d->die)
			{
				print_status(&d->philo_array[i], "died");
				set_end(data);
				return (NULL);
			}
			i++;
		}
		usleep(10);
	}
	return (NULL);
}
