/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:57:46 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/27 13:00:38 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*check_home(t_mini *mini, char *cmd)
{
	int		tilda;

	tilda = check_tilda(cmd);
	get_home(mini);
	return (copy_path(mini, cmd, tilda));
}

int	verify_path(t_mini *mini, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (mini->path[i])
	{
		path = ft_strjoin(mini->path[i], cmd);
		if (!access(path, F_OK))
		{
			mini->correct_path = ft_strdup(path);
			free(path);
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

/*
** function that searches the right executable in every path available
*/
int	find_path(t_mini *mini, char *cmd)
{
	int		tilda;

	if (verify_path(mini, cmd))
		return (1);
	tilda = check_tilda(cmd);
	if (tilda)
		cmd = check_home(mini, cmd);
	if (!access(cmd, F_OK))
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
