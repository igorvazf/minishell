/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:11:09 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/17 01:34:16 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd(t_node *current, t_node *next)
{
	if (!ft_strcmp(next->str[0], "|"))
		//pipe
	else if (!ft_strcmp(next->str[0], "<<"))
		//here doc
	else if (!ft_strcmp(next->str[0], ">>"))
		//append
	else if (!ft_strcmp(next->str[0], ">"))
		//redirect output
	else if (!ft_strcmp(next->str[0], "<"))
		//redirect input
}

int	is_redirect(char c)
{
	if(c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}	

void	run(t_mini *mini, t_list *list)
{
	t_node	*node;

	node = list->begin;
	if (is_delim(node->str[0]))
		exec_cmd(NULL, node);
	while (node != NULL)
	{
		
		node = node->next;
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