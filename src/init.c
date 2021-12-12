/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:57:59 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/11 17:13:42 by paugusto         ###   ########.fr       */
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

void	get_env(t_mini *mini, char **env)
{
	char	**aux;
	int	len;
	int	i;
	int	j;

	len = len_env(env);
	mini->env->key = malloc(sizeof(char *) * len + 1);
	mini->env->content = malloc(sizeof(char *) * len + 1);
	i = 0;
	j = 0;
	while (env[i])
	{
		aux = ft_split(env[i], '=');
		if (aux[0] && aux[1])
		{
			mini->env->key[j] = ft_strdup(aux[0]);
			mini->env->content[j] = ft_strdup(aux[1]);
			j++;
		}
		i++;
		minifree(aux);
	}
	mini->env->key[j] = NULL;
	mini->env->content[j] = NULL;
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
	mini->env->path = ft_split(aux, ':');
	i = 0;
	free(aux);
	while (mini->env->path[i])
	{
		aux = mini->env->path[i];
		mini->env->path[i] = ft_strjoin(aux, "/");
		i++;
		free(aux);
	}
}

void	init(t_mini *mini, char **env)
{
	get_env(mini, env);
	get_path(mini);
	mini->is_open_s = 0;
	mini->is_open_d = 0;
	mini->is_ok = 1;
	mini->init_with_arrow = 0;
}

