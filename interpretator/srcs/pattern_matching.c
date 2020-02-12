/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 00:14:37 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/12 18:40:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char	is_glob(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == ']')
			return (TRUE);
	}
	return (FALSE);
}

static char	**result_pattern(char *line)
{
	char	**res;
	glob_t	globbuf;
	int		j;

	res = NULL;
	glob(line, 0, NULL, &globbuf);
	if (!(res = ft_darnew(globbuf.gl_pathc)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	j = -1;
	while (++j < (int)globbuf.gl_pathc)
		if (!(res[j] = ft_strdup(globbuf.gl_pathv[j])))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
	globfree(&globbuf);
	return (res);
}

static int	count_pattern(char *line)
{
	int		res;
	glob_t	globbuf;

	res = 0;
	glob(line, 0, NULL, &globbuf);
	res += globbuf.gl_pathc;
	globfree(&globbuf);
	return (res);
}

static int	count_patterns(char **args)
{
	int		i;
	int		counter;

	i = -1;
	counter = 0;
	while (args[++i])
	{
		if (is_glob(args[i]))
			counter += count_pattern(args[i]);
		else
			++counter;
	}
	return (counter);
}

char		**pattern_matching(char **args)
{
	char	**tmp;
	char	**res;
	int		i;
	int		k;
	int		j;

	i = -1;
	j = -1;
	res = ft_darnew(count_patterns(args));
	while (args[++i])
	{
		if (is_glob(args[i]) && count_pattern(args[i]))
		{
			tmp = result_pattern(args[i]);
			ft_strdel(&args[i]);
			k = -1;
			while (tmp[++k])
				res[++j] = tmp[k];
			free(tmp);
		}
		else
			res[++j] = args[i];
	}
	return (res);
}