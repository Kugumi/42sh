/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:55:40 by filip             #+#    #+#             */
/*   Updated: 2019/04/28 00:55:26 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include <dirent.h>
# include <unistd.h>
# include "libft.h"
# define MAXDIR 4097

void			cd(int argc, char **argv, char **env_cp);
char			check_ch_dir(int argc , char **argv);
char			check_request(int argc, char  **argv);
#endif