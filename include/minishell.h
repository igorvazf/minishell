/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:10 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/18 18:03:15 by paugusto         ###   ########.fr       */
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
# include <signal.h>

# define D_QUOTE '\"'
# define S_QUOTE '\''
# define DELIM "|<>"

/*
** Linked list structure - Commands
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
	t_node	*node;
	size_t	size;
}	t_list;

/*
** Linked list structure - Environment Variables
*/
typedef struct s_nodenv
{
	char			*key;
	char			*content;
	struct s_nodenv	*next;
}	t_nodenv;

typedef struct s_env
{
	t_nodenv	*begin;
	t_nodenv	*end;
	size_t		size;
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
	char	**path;
	char	*input;
	char	*input_sanitized;
	char	*correct_path;
	int		init_with_arrow;
	int		is_open_s;
	int		is_open_d;
	int		pipe;
	int		redir;
	int		out;
	int		in;
	t_env	*env;
}	t_mini;


/*
** Double linked list functions
*/
t_list	*create_list(void);
void	push_node(t_list *list, char *str);
void	free_list(t_list **list_ref);
t_env	*create_env(void);
void	push_env(t_env *env, char *key, char *content);
void	free_env(t_env **env_ref);
void	print_elements(t_list *list);
void	print_env(t_env *env);


/*
** Minishell functions
*/
void	minifree(char **ptr);
void	free_em_all(t_mini *mini);
void	init(t_mini *mini, char **environ);
void	free_reset(t_mini *mini, t_list *list);
void	is_in_quote(char c, t_mini *mini);
int		split_cmd(t_mini *mini, t_list *list);
void	input_sanitizer(t_mini *mini);
int		is_builtin(t_node *node);
void	execute_builtin(int builtin, t_node *node, t_mini *mini, t_list *list);
void	find_path(t_mini *mini, t_list *list);
int		ministrcmp(char *s1, char *s2);
int		is_redirect(char c);

void	execute(t_mini *mini, t_list *list, t_node *node);


/* Builtins */
void	miniexit(t_mini *mini, t_list *list);
void	miniunset(t_env *env, t_node *node);
void	minipwd(void);
void	minicd(t_node *node);
void	miniecho(t_node *node);
void	minienv(t_env *env);
void	miniexport(t_env *env, t_node *node);






#endif
