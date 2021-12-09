/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:10 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/09 14:50:24 by paugusto         ###   ########.fr       */
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
** env -> pointer to env structure
*/
typedef struct s_mini
{
	char	*input;
	char	*input_sanitized;
	int		is_open;
	t_env	*env;
}	t_mini;

/*
** Double linked list functions
*/
t_list	*create_list(void);
t_node	*create_node(char *str);
void	destroy_list(t_list **list_ref);
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
void	split(t_mini *mini);
void	is_quotes_closed(t_mini *mini);

#endif
