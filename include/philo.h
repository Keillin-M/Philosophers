/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:29:25 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/26 11:36:46 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			meal_count;
	s_data		*data;
	pthread_t	*thread;
}	t_philo;

typedef struct s_data
{
	int				philos;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	int				start_time;
	mutex			print_lock;
	t_philo			*philo_array;
	pthread_mutex_t	*forks;
}	t_data;

#endif
