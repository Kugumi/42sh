/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bin_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:09:54 by filip             #+#    #+#             */
/*   Updated: 2019/09/21 19:02:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_bin_table(t_bin_table *bin_table)
{
	bin_table->bin_table = free_hash_table(bin_table->bin_table,
	bin_table->bin_table_size);
	bin_table->bin_table_size = 0;
}
