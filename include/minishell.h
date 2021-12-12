/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:10 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/11 19:42:29 by paugusto         ###   ########.fr       */
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
# include <stdbool.h>

# define MAXCOM 1000
# define MAXLIST 100
# define D_QUOTE '\"'
# define S_QUOTE '\''
# define DELIM "|<>"

/*
** Linked list structure - Node
*/
typedef struct s_node
{
	char			**str;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

/*
** Linked list strucute - List
*/
typedef struct s_list
{
	t_node	*begin;
	t_node	*end;
	size_t	size;
}	t_list;

/*
** Environment variables strucute
*/
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
** is_open -> int value to check quoting
** env -> pointer to env structure
** list -> pointer to a linked lis
*/
typedef struct s_mini
{
	char	*input;
	char	*input_sanitized;
	char	*correct_path;
	char	**io;
	int		is_open_s;
	int		is_open_d;
	int		is_ok;
	int		init_with_arrow;
	int		pipe;
	t_env	*env;
}	t_mini;

/*
** Double linked list functions
*/
t_list	*create_list(void);
t_node	*create_node(char *str);
void	destroy_list(t_list *list);
bool	is_list_empty(const t_list *list);
void	add_first(t_list *list, char *str);
void	add_last(t_list *list, char *str);
void	print_elements(t_list *list);
void	print_inverted_elements(t_list *list);

/*
** Minishell functions
*/
void	minipwd(void);
void	miniheader(void);
void	get_input(t_mini *mini);
void	input_sanitizer(t_mini *mini);
void	init(t_mini *mini, char **env);
void	is_quotes_closed(t_mini *mini);
void	execute(t_mini *mini, t_list *list);
void	find_path(t_mini *mini, t_list *list);
void	is_in_quote(char c, t_mini *mini);
int		split_cmd(t_mini *mini, t_list *list);
void	free_em_all(t_mini *mini, t_list *list);
void	free_minishell(t_mini *mini);
void	minifree(char **ptr);

#endif
