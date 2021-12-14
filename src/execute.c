/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:11:09 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/14 15:21:35 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	fd_handler(t_mini *mini)
{
	if (mini->in != 0)
	{
		dup2(mini->in, 0);
		close(mini->in);
	}
	if (mini->out != 1)
	{
		dup2(mini->out, 1);
		close(mini->out);
	}
}

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
		signals(2);
		find_path(mini, list);
		if (pid < 0)
			;
		else if (pid == 0)
		{
			//child -> executar o comando 
			fd_handler(mini);
			execve(mini->correct_path, node->str, NULL);
			//exit
		}
		else
			wait(&pid);
	}
}

void	run(t_mini *mini, t_list *list)
{
	t_node *node;
	int	fd[2];
	//fd[0] -> read end, entrada de dados
	//fd[1] -> write end, saida de dados
	int	i;
	int	j;
	
	i = 0;
	j = mini->pipe + mini->redir;
	node = list->begin;
	while (i < j)
	{
		if (pipe(fd) < 0)
			;
		mini->out = fd[1]; //mudando a saida padrao para o fd[0]
		execute(mini, list, node);
		close(fd[1]);
		if (mini->in != 0)
			close(mini->in);
		mini->in = fd[0]; //mudar a entrada padrao para o 0
		node = node->next;
		i++;
	}
	execute(mini, list, node);
}