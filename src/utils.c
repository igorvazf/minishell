/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:58:10 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/26 14:35:08 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	is_in_quote(char c, t_mini *mini)
{
	if (c == S_QUOTE)
	{
		if (mini->is_open_s == 0 && mini->is_open_d == 0)
			mini->is_open_s = 1;
		else if (mini->is_open_s == 1)
		{
			mini->is_open_s = 0;
			mini->final_s = 1;
		}
	}
	if (c == D_QUOTE)
	{
		if (mini->is_open_d == 0 && mini->is_open_s == 0)
			mini->is_open_d = 1;
		else if (mini->is_open_d == 1)
		{
			mini->is_open_d = 0;
			mini->final_d = 1;
		}
	}
}

int	is_redirect(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	get_home(t_mini *mini)
{
	t_nodenv	*env;

	env = mini->env->begin;
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, "HOME"))
			break;
		env = env->next;
	}
	if(env->content)
	{
		free(mini->home);
		mini->home = ft_strdup(env->content);
	}
}

int	check_tilda(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '~')
			j++;
		i++;
	}
	return (j);
}

char	*copy_path(t_mini *mini, char *cmd, int tilda, int k)
{
	char	*aux;
	int		len_home;
	int		i;
	int		j;

	len_home = ft_strlen(mini->home);
	i = 0;
	j = 0;
	if (cmd[i] == '~')
		len_home++;
	aux = malloc(sizeof(char) * len_home + ft_strlen(cmd) + 1 - tilda);
	while (cmd[i])
	{
		if (cmd[i] != '~')
			aux[j++] = cmd[i++];
		else
		{
			if (i != 0)
				k++;
			while (mini->home[k])
				aux[j++] = mini->home[k++];
			k = 0;
			i++;
		}
	}
	aux[j] = '\0';
	return (aux);
}

char	*check_home(t_mini *mini, char *cmd)
{
	int		tilda;

	tilda = check_tilda(cmd);
	get_home(mini);
	return (copy_path(mini, cmd, tilda, 0));
}

int	find_path(t_mini *mini, char *cmd)
{
	char	*path;
	int		i;
	int		j;
	int		tilda;

	i = -1;
	j = 0;
	while (i < 0 && mini->path[j])
	{
		path = ft_strjoin(mini->path[j], cmd);
		i = access(path, F_OK);
		if (i >= 0)
		{
			mini->correct_path = ft_strdup(path);
			free(path);
			return (1);
		}
		free(path);
		j++;
	}
	tilda = check_tilda(cmd);
	if (tilda)
		cmd = check_home(mini, cmd);
	i = access(cmd, F_OK);
	if (i >= 0)
	{
		mini->correct_path = ft_strdup(cmd);
		return (1);
	}
	if (ft_strlen(cmd) > 0)
		printf("error command not found\n");
	if (tilda)
		free(cmd);
	return (0);
}

