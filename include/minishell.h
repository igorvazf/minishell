/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:10 by igvaz-fe          #+#    #+#             */
/*   Updated: 2022/01/01 01:13:52 by paugusto         ###   ########.fr       */
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

typedef struct s_sani
{
	int		i;
	int		j;
	int		s;
	int		d;
}	t_sani;

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
	char	*home;
	int		init_with_arrow;
	int		is_open_s;
	int		is_open_d;
	int		final_s;
	int		final_d;
	int		pipe;
	int		redir;
	int		out;
	int		in;
	int		st_out;
	int		st_in;
	int		command_fail;
	t_env	*env;
}	t_mini;

extern int	g_return;

/*
** linked list functions
*/
t_list	*create_list(void);
void	push_node(t_list *list, char *str);
void	free_list(t_list **list_ref);
t_env	*create_env(void);
void	push_env(t_env *env, char *key, char *content);
void	free_env(t_env **env_ref);
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
void	input_sanitizer(t_mini *mini, t_sani *sani);
int		is_builtin(t_node *node);
void	execute_builtin(int builtin, t_node *node, t_mini *mini, t_list *list);
int		find_path(t_mini *mini, char *cmd);
int		is_redirect(char c);
int		redirect_out(t_mini *mini, t_node *node, int i);
int		redirect_in(t_mini *mini, t_node *node, int i);
void	run(t_mini *mini, t_list *list);
void	fd_handler(t_mini *mini);
void	get_cmd(t_mini *mini, t_node *node);
void	get_input(t_mini *mini, t_sani *sani);
int		validade(t_list *list);
int		check_tilda(char *cmd);
void	get_home(t_mini *mini);
char	*copy_path(t_mini *mini, char *cmd, int tilda);
void	get_home(t_mini *mini);
int		len_node(char **str);
void	expand_var(t_mini *mini, t_node *node, int i);
void	signals(int signum);
void	get_cmd_builtin(t_mini *mini, t_node *node);

/* Builtins */
void	miniexit(t_mini *mini, t_list *list);
void	miniunset(t_env *env, t_node *node);
void	minipwd(void);
void	minicd(t_mini *mini, t_node *node);
void	miniecho(t_mini *mini, t_node *node);
void	minienv(t_env *env);
void	miniexport(t_env *env, t_node *node);

#endif
