/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:32:40 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 13:34:32 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_free_redir(int **red)
{
	int i;

	if (!red)
		return ;
	i = -1;
	while (red[++i])
		free(red[i]);
	free(red);
}

void	ft_free_r(t_redir_list *r)
{
	if (!r)
		return ;
	ft_free_r(r->next);
	free(r);
}

void	ft_free_proc(t_process *p)
{
	if (!p)
		return ;
	ft_free_proc(p->next);
	ft_free_r(p->r);
	cls_redir(p->fd_list);
	if (p->args)
		ft_free_dar(p->args);
	ft_free_redir(p->fd_list);
	free(p);
}

void	ft_free_jobs(t_job *j)
{
	if (!j)
		return ;
	ft_free_jobs(j->next);
	ft_free_proc(j->first_process);
	if (j->command)
		free(j->command);
	free(j);
}
