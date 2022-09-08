/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 15:10:52 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/08 17:16:39 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

long	parse_arg_to_long(char *argv, long max)
{
	long long	count;

	count = 0;
	if (!*argv)
		return (-1);
	while (*argv >= '0' && *argv <= '9')
	{
		count = count * 10 + (*argv - '0');
		if (count > max)
			return (-1);
		argv++;
	}
	if (*argv != '\0')
		return (-1);
	return (count);
}