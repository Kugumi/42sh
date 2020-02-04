/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_double_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 14:32:43 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/04 19:21:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_double_quotes(char **str, size_t *pos)
{
	char	*new_line;
	size_t	offset;

	if (!str || !pos)
		return (T_ERR);
	offset = 1;
	while (lex_is_open_dq(*str, *pos, &offset))
	{
		if (!(*str = lex_add_eol(*str)))
			return (T_ERR);
		if (!(new_line = ft_readline(get_var("PS2", ALL_VARS))))
			return (T_ERR);
		if (*new_line == RL_K_CTRL_C)
			return (lex_ctrl_c(str, &new_line));
		if (!(*str = lex_strjoin(*str, new_line)))
			return (T_ERR);
	}
	(*pos) += offset + 1;
	return (T_NULL);
}

int				lex_is_open_dq(char *str, size_t pos, size_t *offset)
{
	if (!str || !offset)
		return (0);
	while (str[pos + *offset])
	{
		if (str[pos + *offset] == '"')
			if (!lex_is_esc_dq(str, pos + *offset))
				return (0);
		(*offset)++;
	}
	return (1);
}

size_t			lex_is_esc_dq(char *str, size_t pos)
{
	if (!str)
		return (0);
	if (pos > pos - 1)
		if (!ft_strncmp(str + pos - 1, "\\\"", 2))
			return (1);
	return (0);
}
