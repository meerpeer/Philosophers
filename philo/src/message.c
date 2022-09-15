/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 11:45:05 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/15 11:18:02 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

void	write_message(int current_time, t_action action, int index)
{
	if (action == TAKE_FORK)
		printf("%i %i has taken a fork\n", current_time, index);
	else if (action == EAT)
		printf("%i %i is eating\n", current_time, index);
	else if (action == SLEEP)
		printf("%i %i is sleeping\n", current_time, index);
	else if (action == EAT)
		printf("%i %i is thinking\n", current_time, index);
	else if (action == DIE)
		printf("%i %i died\n", current_time, index);
}
