/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:43:41 by paugusto          #+#    #+#             */
/*   Updated: 2021/11/30 19:53:59 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_cmd(t_mini *mini, char *command)
{
	char	*path;
	int		i;

	i = 0;
	while (mini->input_parsed)
	{
		path = ft_strjoin(mini->path[i], command);
		if(execve(path, mini->input_parsed, NULL) == -1)
			i++;
		else
			return ;
	}
	printf("minishell: command not found: %s", command);
}
