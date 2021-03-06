/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:01 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/15 21:06:09 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int				ft_octal(char **argv, int i, int j)
{
	int				octcount;
	int				oct;

	oct = 0;
	octcount = 3;
	if (ft_isoct(argv[i][j + 1]))
	{
		j++;
		while (argv[i][j] && ft_isoct(argv[i][j]) && octcount--)
		{
			oct = (oct * 8) + argv[i][j] - 48;
			j++;
		}
		ft_putchar_fd((char)oct, STDOUT_FILENO);
		j--;
	}
	return (j);
}

int				ft_common_escape(char **argv, int i, int j)
{
	if (argv[i][j] == 'n')
		ft_putchar_fd('\n', STDOUT_FILENO);
	else if (argv[i][j] == 'a')
		ft_putchar_fd('\a', STDOUT_FILENO);
	else if (argv[i][j] == 'b')
		ft_putchar_fd('\b', STDOUT_FILENO);
	else if (argv[i][j] == 'f')
		ft_putchar_fd('\f', STDOUT_FILENO);
	else if (argv[i][j] == 'r')
		ft_putchar_fd('\r', STDOUT_FILENO);
	else if (argv[i][j] == 't')
		ft_putchar_fd('\t', STDOUT_FILENO);
	else if (argv[i][j] == 'v')
		ft_putchar_fd('\v', STDOUT_FILENO);
	else if (argv[i][j] == '\\')
		ft_putchar_fd('\\', STDOUT_FILENO);
	else
		return (0);
	return (1);
}

static int		ft_check_whole_arg(int *tmp_flags, int i, int j, char **argv)
{
	if (argv[i][j] == 'n')
		tmp_flags[0] = 1;
	else if (argv[i][j] == 'e' || argv[i][j] == 'E')
	{
		if (argv[i][j] == 'e')
			tmp_flags[1] = 1;
		else
			tmp_flags[1] = 0;
	}
	else
		return (i - 1);
	return (i);
}

static int		ft_echoflags(int *flags, char **argv)
{
	int				i;
	int				j;
	int				tmp_flags[2];

	i = 1;
	while (argv[i] && argv[i][0] == '-' && argv[i][1])
	{
		ft_bzero(tmp_flags, 2 * sizeof(int));
		j = 1;
		while (argv[i][j])
		{
			if (ft_check_whole_arg(tmp_flags, i, j, argv) != i)
				return (i);
			j++;
		}
		flags[0] = (flags[0] | tmp_flags[0]);
		flags[1] = (flags[1] | tmp_flags[1]);
		i++;
	}
	return (i);
}

int				ft_echo(int argc, char **argv, char **environ)
{
	int				i;
	int				flags[3];

	(void)environ;
	if (fcntl(1, F_GETFD) == -1)
	{
		err("42sh", argv[0], EBADFD, "write error");
		return (EXIT_FAILURE);
	}
	ft_bzero(flags, 3 * sizeof(int));
	i = ft_echoflags(flags, argv);
	if (flags[1] == 1)
		i = ft_eflag(i, argv, argc, flags);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argc != i)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flags[0] == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
