/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:11:09 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/11 19:00:21 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_mini *mini, t_list *list)
{
	int	pid;

	find_path(mini, list);
	pid = fork();
	if(pid != -1)
	{
		if (pid == 0)
		{
			execve(mini->correct_path, list->end->str, NULL);
		}
		else
		{
			wait(&pid);
		}
	}
}
