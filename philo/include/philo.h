/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:05:12 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/08 17:17:09 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;

struct s_philo
{
	t_info				*info;
	pthread_t			thread;
	pthread_mutex_t	fork;
	int					index;
	long				time_to_eat;
	int					nr_of_eats;
};

struct s_info
{
	t_philo	*philos;
	int		nr_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nr_times_to_eat;
	int		nr_fully_fed_philo;
	int		one_dead;
};

long	parse_arg_to_long(char *argv, long max);

#endif