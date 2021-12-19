/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:15:00 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/19 16:20:53 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect_out(t_mini *mini, t_node *node, int i)
{
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	if (node->str[i + 1][0] == '>' || node->str[i + 1][0] == '<'
		|| node->str[i + 1][0] == '\0')
		return (0);
	file = ft_strdup(node->str[i + 1]);
	if (!ft_strcmp(node->str[i], ">>"))
	{
		mini->out = open(file, flags | O_APPEND, 0777);
		free(file);
		return (1);
	}
	else if (!ft_strcmp(node->str[i], ">"))
	{
		mini->out = open(file, flags | O_TRUNC, 0777);
		free(file);
		return (1);
	}
	return (0);
	//armazenar a info de que out foi o ultimo?
}

int	redirect_in(t_mini *mini, t_node *node)
{
	char	*file;

	file = ft_strdup(node->str[1]);
	if (!ft_strcmp(node->str[0], "<"))
	{
		mini->in = open(file, O_RDONLY, 0777);
	}
	free(file);
	//armazenar a info de que in foi o ultimo?
	return (0);
}
