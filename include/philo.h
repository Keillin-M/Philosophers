/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:29:25 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/04 16:09:26 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_philo
{
	int				id;
	long			last_meal;
	int				meal_count;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	meal_count_lock;
};

struct s_data
{
	int				philos;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	long			start_time;
	int				end;
	pthread_t		monitor_thread;
	pthread_t		monitor_eat;
	t_philo			*philo_array;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
};

// philo.c
int		check_end(t_data *data);
void	set_end(t_data *data);

// init.c
int		ft_init(t_data *data);
int		create_thread(t_data *data);
int		join_thread(t_data *data);

// routine.c
long	get_last_meal(t_philo *philo);
void	set_last_meal(t_philo *philo);
int		get_meal_count(t_philo *philo);
void	increase_meal(t_philo *philo);
void	*routine(void *data);

// monitor.c
void	*monitor_eat_enough(void *data);
void	*monitor_death(void *data);

// fork.c
void	pick_fork(t_philo *philo);
void	drop_fork(t_philo *philo);

// utils.c
long	get_time(void);
void	print_status(t_philo *philo, char *status);
int		parse_int(const char *nptr);
void	ft_clean(t_data *data);

#endif
