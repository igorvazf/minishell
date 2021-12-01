/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:10 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/11/30 20:56:00 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# define MAXCOM 1000
# define MAXLIST 100

typedef struct s_mini
{
	char	*input;
	char	***input_parsed;
	char	**path;
	int		pipes;
}	t_mini;

void	minipwd(void);
void	miniheader(void);
void	init(t_mini *mini);
void	get_input(t_mini *mini);
void	process_input(t_mini *mini);

#endif
