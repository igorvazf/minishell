/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:11:09 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/15 03:09:32 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_mini *mini, t_list *list, t_node *node)
{
	int	pid;
	int	builtin;

	builtin = is_builtin(node);
	if (builtin)
		execute_builtin(builtin, node, mini, list);
	else
	{
		pid = fork();
		//signals(2);
		find_path(mini, list);
		if (pid < 0)
			;
		else if (pid == 0)
		{
			//child -> executar o comando 
			//fd_handler(mini);
			execve(mini->correct_path, node->str, NULL);
			//exit
		}
		else
			wait(&pid);
	}
}