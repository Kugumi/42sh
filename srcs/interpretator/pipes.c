/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:01:04 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/21 22:44:29 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	pipe_op(t_node *ast)
{
	int	pipes[2];
	int	pid[2];

	if (pipe(pipes) != 0)
		err_exit("pipe() error", NULL, NOERROR);
	left_child(&pid[0], pipes, ast->left);
	right_child(&pid[1], pipes, ast->right);
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid[0], 0, 0);
	waitpid(pid[1], 0, 0);
}

void	left_child(int *pid, int *pipes, t_node *expr)
{
	int	fd;

	if ((*pid = make_process()) == 0)
	{
		close(pipes[0]);
		if ((fd = dup(STDOUT_FILENO)) == -1)
			err_exit("dup() error", NULL, NOERROR);
		close(STDOUT_FILENO);
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			err_exit("dup2() error", NULL, NOERROR);
		interpret_ast(expr);
		if (dup2(fd, STDOUT_FILENO) == -1)
			err_exit("dup2() error", NULL, NOERROR);
		exit(EXIT_SUCCESS);
	}
}

void	right_child(int *pid, int *pipes, t_node *expr)
{
	int	fd;

	if ((*pid = make_process()) == 0)
	{
		close(pipes[1]);
		if ((fd = dup(STDIN_FILENO)) == -1)
			err_exit("dup() error", NULL, NOERROR);
		close(STDIN_FILENO);
		if (dup2(pipes[0], STDIN_FILENO) == -1)
			err_exit("dup2() error", NULL, NOERROR);
		interpret_ast(expr);
		if (dup2(fd, STDIN_FILENO) == -1)
			err_exit("dup2() error", NULL, NOERROR);
		exit(EXIT_SUCCESS);
	}
}
