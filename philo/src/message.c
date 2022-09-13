/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 11:45:05 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/13 12:16:57 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

void	write_message(t_info *info, t_action action, int index)
{
	pthread_mutex_lock(&info->write_lock);
	printf("");
	pthread_mutex_unlock(&info->write_lock);
}