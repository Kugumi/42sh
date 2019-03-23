/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:29:20 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/23 18:25:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	get_count_var(char *arr, char **environ)
{
	uint8_t	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], arr, ft_strlen(arr)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_var(char *arr, char **environ)
{
	return (&(environ[get_count_var(arr, environ)][ft_strlen(arr) + 1]));
}

void	print_environ(char **environ)
{
	short	i;

	i = -1;
	while (environ[++i])
	{
		ft_putstr(environ[i]);
		ft_putchar('\n');
	}
}