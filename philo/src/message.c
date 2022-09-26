/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 11:45:05 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/26 16:47:41 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_message(t_info *info, t_action action, int index)
{
	int	current_time;

	current_time = get_elapsed_time(info);
	pthread_mutex_lock(info->write_lock);
	if (action == TAKE_FORK)
		printf("%i %i has taken a fork\n", current_time, index);
	else if (action == EAT)
		printf("%i %i is eating\n", current_time, index);
	else if (action == SLEEP)
		printf("%i %i is sleeping\n", current_time, index);
	else if (action == THINK)
		printf("%i %i is thinking\n", current_time, index);
	else if (action == DIE)
		printf("%i %i died\n", current_time, index);
	pthread_mutex_unlock(info->write_lock);
}
