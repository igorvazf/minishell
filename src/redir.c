/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:15:00 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/18 14:36:37 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect_out(t_struct *mini, t_node *node, t_node *next)
{
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	file = ft_substr(node->str[1]);
	if (ft_strncmp(node->str[0], ">>") && !is_redirect(node->str[1]))
	}
		mini->out = open(file, flags | O_APPEND, 0777);
		free(file);
		return (1);
	}
	else if (ft_strncmp(node->str[0], ">") && !is_redirect(node->str[1]))
	{
		mini->out = open(file, flags | O_TRUNC, 0777);
		free(file);
		return (1);
	}
	return (0);
	//armazenar a info de que out foi o ultimo?
}

int	redirect_in(t_struct *mini, t_node *node)
{
	char	*file;

	file = ft_substr(node->str[1]);
	if (ft_strncmp(node->str[0], "<") && !is_redirect(node->str[1]))
	{
		mini->in = open(file, O_RDONLY, 0777);
	}
	free(file);
	//armazenar a info de que in foi o ultimo? 
}