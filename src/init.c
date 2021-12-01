/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:57:59 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/01 19:56:24 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_path(t_mini *mini)
{
	char	*path;
	char	*aux;
	int		i;

	path = getenv("PATH");
	aux = ft_strdup(path);
	if(!aux)
		return ;
	mini->path = ft_split(aux, ':');
	i = 0;
	while (mini->path[i])
	{
		mini->path[i] = ft_strjoin(mini->path[i], "/");
		i++;
	}
	free(aux);
}

void	init(t_mini *mini)
{
	get_path(mini);
	mini->n_pipes = 0;
	mini->is_quotes_closed = 1;
	mini->n_rredirects = 0;
	mini->n_lredirects = 0;
	mini->n_rhere_docs = 0;
	mini->n_lhere_docs = 0;
}
