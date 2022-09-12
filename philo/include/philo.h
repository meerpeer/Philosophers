/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:05:12 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/12 10:43:24 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}			t_bool;

struct s_philo
{
	t_info				*info;
	pthread_t			thread;
	//pthread_mutex_t		philo_lock;
	int					index;
	long				time_to_death;
	int					nr_of_eats;
	int					fork_id1;
	int					fork_id2;
};

struct s_info
{
	t_philo			*philos;
	int				nr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nr_times_to_eat;
	int				nr_fully_fed_philo;
	t_bool			one_dead;
	pthread_mutex_t	one_dead_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
};

long	parse_arg_to_long(char *argv, long max);
t_bool	parse_input_to_info(int argc, char **argv, t_info *info);
t_bool	init_philos(t_info *info);
t_bool	init_forks(t_info *info);

#endif