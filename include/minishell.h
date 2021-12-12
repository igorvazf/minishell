/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:10 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/12 16:40:28 by paugusto         ###   ########.fr       */
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
# define DELIM "|<>"

/*
** Linked list structure - Node and List
*/
typedef struct s_node
{
	char			**str;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*begin;
	t_node	*end;
	size_t	size;
}	t_list;

/*
** Linked list structure - variables strucute
*/
typedef struct s_node_env
{
	char				*key;
	char				*content;
	struct s_node_env	*next;
}	t_node_env;

typedef struct s_list_env
{
	t_node_env	*begin;
	t_node_env	*end;
	size_t		size;
}	t_list_env;

/*
** input -> line read from terminal (raw, no treats)
** input_sanitized -> input ready to work with
** is_open -> int value to check quoting
** env -> pointer to env structure
** list -> pointer to a linked lis
*/
typedef struct s_mini
{
	char		*input;
	char		*input_sanitized;
	char		*correct_path;
	char		**io;
	char		**path;
	int			is_open_s;
	int			is_open_d;
	int			is_ok;
	int			init_with_arrow;
	int			pipe;
	t_list_env	*env;
}	t_mini;

/*
** Double linked list functions
*/
t_list		*create_list(void);
t_node		*create_node(char *str);
void		destroy_list(t_list *list);
void		add_last(t_list *list, char *str);
void		print_elements(t_list *list);
t_list_env	*create_list_env(void);
t_node_env	*create_node_env(char *key, char *content);
void		add_last_env(t_list_env *list, char *key, char *content);
void		destroy_list_env(t_list_env *list);
void		print_env(t_list_env *list);

/*
** Minishell functions
*/
void	miniheader(void);
void	get_input(t_mini *mini);
void	input_sanitizer(t_mini *mini);
void	init(t_mini *mini, char **environ);
void	is_quotes_closed(t_mini *mini);
void	execute(t_mini *mini, t_list *list);
void	find_path(t_mini *mini, t_list *list);
void	is_in_quote(char c, t_mini *mini);
int		split_cmd(t_mini *mini, t_list *list);
void	free_em_all(t_mini *mini, t_list *list);
void	free_minishell(t_mini *mini);
void	minifree(char **ptr);

/* builtins */
void	miniecho(t_node *node);
void	minicd(t_node *node);
void	minipwd(void);
void	miniexit(t_mini *mini, t_list *list);
void	minienv(t_list_env *env);

#endif
