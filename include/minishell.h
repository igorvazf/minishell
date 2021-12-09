/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:10 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/06 11:58:59 by paugusto         ###   ########.fr       */
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
# define D_QUOTE '\"'
# define S_QUOTE '\''


typedef struct s_env
{
	char	**env;
	char	**key;
	char	**content;
	char	**path;
	int		len;
}	t_env;

/*
** input -> line read from terminal (raw, no treats)
** input_sanitized -> input ready to work with
** env -> pointer to env structure
*/
typedef struct s_mini
{
	char	*input;
	char	*input_sanitized;
	int		is_open;
	t_env	*env;
}	t_mini;

void	minipwd(void);
void	miniheader(void);
void	get_input(t_mini *mini);
void	input_sanitizer(t_mini *mini);
void	init(t_mini *mini, char **env);
void	split(t_mini *mini);
void	is_quotes_closed(t_mini *mini);

#endif
