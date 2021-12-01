/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:10 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/01 20:24:57 by paugusto         ###   ########.fr       */
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
# define REDIRECTS "|"

/*
** input -> linha lida do readline
** input_parsed -> input divido em blocos de comandos
** path -> variavel path dividida em blocos
** red_order -> ordem dos redirecionamentos de arquivos
** n_pipes -> numero de pipes "|"
** n_rredirects -> numero de redirects ">"
** n_lredirects -> nummero de redirects "<"
** n_rhere_docs -> numero de here docs ">>"
** n_lhere_docs -> numero de here docs "<<"
** is_quotes_closed -> verifica se as aspas estao fechadas
*/
typedef struct s_mini
{
	char	*input;
	char	***input_parsed;
	char	*red_order;
	char	**path;
	int		n_pipes;
	int		n_rredirects;
	int		n_lredirects;
	int		n_rhere_docs;
	int		n_lhere_docs;
	int		is_quotes_closed;
}	t_mini;

void	minipwd(void);
void	miniheader(void);
void	init(t_mini *mini);
void	get_input(t_mini *mini);
void	process_input(t_mini *mini);

#endif
