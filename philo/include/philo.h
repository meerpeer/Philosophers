/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:05:12 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/15 11:44:12 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;

typedef enum e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}			t_action;

struct s_philo
{
	t_info				*info;
	pthread_t			thread;
	pthread_mutex_t		philo_lock;
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
	int				start_time;
	int				current_time;
	bool			done;
	pthread_mutex_t	info_lock;
	pthread_mutex_t	*forks;
};

long	parse_arg_to_long(char *argv, long max);
bool	parse_input_to_info(int argc, char **argv, t_info *info);
bool	initialize(t_info *info);
// bool	init_philos(t_info *info);
// bool	init_forks(t_info *info);
// bool	init_info_mutexes(t_info *info);

void	free_info_contents(t_info *info);
bool	destroy_mutexes(t_info *info, int fork_mutexes, int philo_mutexes,
	bool info_lock_created);

int		get_time_in_ms(void);
void	set_current_time(t_info *info);
void	write_message(int current_time, t_action action, int index);

void	*philosopher(void *data);

#endif