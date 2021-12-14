/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:57:59 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/14 15:10:11 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	len_env(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

void	get_env(t_list_env *env, char **environ)
{
	char	**aux;
	int	len;
	int	i;

	len = len_env(environ);
	i = 0;
	while (environ[i])
	{
		aux = ft_split(environ[i], '=');
		add_last_env(env, aux[0], aux[1]);
		i++;
		minifree(aux);
	}
}

void	get_path(t_mini *mini)
{
	char	*path;
	char	*aux;
	int		i;

	path = getenv("PATH");
	aux = ft_strdup(path);
	if(!aux)
		return ;
	mini->path = ft_split(aux, ':');
	i = 0;
	free(aux);
	while (mini->path[i])
	{
		aux = mini->path[i];
		mini->path[i] = ft_strjoin(aux, "/");
		i++;
		free(aux);
	}
}

void	init(t_mini *mini, char **environ)
{
	get_env(mini->env, environ);
	get_path(mini);
	mini->is_open_s = 0;
	mini->is_open_d = 0;
	mini->is_ok = 1;
	mini->init_with_arrow = 0;
	mini->correct_path = NULL;
	mini->io = NULL;
}

