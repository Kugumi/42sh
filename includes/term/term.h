/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:03:47 by filip             #+#    #+#             */
/*   Updated: 2019/09/23 22:44:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# define RUNNING 1
# define INIT_FLAGS 0
# define LINE_MAX 2048
# define TERM_SIGINT (1 << 1)
# define TERM_EXIT (1 << 2)
/*
**	ft_term.c
*/
void				term_start(void);
void				check_valid_string(char *buffer);
/*
**	global_var.c
*/
void				init_global_var(char **argv, char **environ);
void				free_globar_var(void);

unsigned char	g_flags;
char			**g_argv;
#endif
