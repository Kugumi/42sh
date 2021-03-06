/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:44:13 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/15 22:16:11 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static int		write_here_doc(char **buf)
{
	int fd;

	fd = ft_open(HEREDOC_FILE, O_RDWR | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		ft_free_dar(buf);
		return (-1);
	}
	while (*buf)
	{
		ft_putstr_fd(*buf++, fd);
		ft_putchar_fd('\n', fd);
	}
	lseek(fd, 0, SEEK_SET);
	return (fd);
}

static char		**check_inp(char *line, char **buf)
{
	if (*line == RL_K_CTRL_C)
	{
		g_last_exit_status = 1;
		set_var("?", "1", ALL_VARS);
		ft_free_dar(buf);
		buf = NULL;
	}
	free(line);
	return (buf);
}

static char		**read_heredoc(char const *delim)
{
	t_her_vars v;

	v.i = 0;
	v.buf_size = DEF_HEREDOC_SIZE;
	if (!(v.buf = (char **)ft_memalloc(sizeof(char *) * v.buf_size)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	while ((v.tmp = ft_readline("heredoc> ")) && ft_strcmp(v.tmp, delim)
	&& *v.tmp != RL_K_CTRL_D && *v.tmp != RL_K_CTRL_C)
	{
		v.buf[v.i++] = v.tmp;
		if (v.i >= v.buf_size - 1)
		{
			if (!(v.buf = (char **)ft_realloc(v.buf, sizeof(char *) *
			v.buf_size, sizeof(char *) * (v.buf_size * 2))))
				err_exit("42sh", "malloc() error", NULL, NOERROR);
			v.buf_size *= 2;
		}
	}
	return (check_inp(v.tmp, v.buf));
}

int				here_doc(t_lex_tkn **list, t_process *curr, int io_number)
{
	char	**buf;
	int		fd;

	if (io_number < 0)
		io_number = 0;
	list++;
	if (!(buf = read_heredoc((*list)->value)))
		return (-1);
	if ((fd = write_here_doc(buf)) < 0)
	{
		err("42sh", "failed to create heredoc file", NULL, HEREDOC_FILE);
		return (-1);
	}
	ft_free_dar(buf);
	add_redir(curr, fd, io_number);
	return (0);
}
