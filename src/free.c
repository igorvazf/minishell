/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:54:03 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/11 19:27:40 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_em_all(t_mini *mini, t_list *list)
{
	destroy_list(&list);
	free(mini->input);
	free(mini->input_sanitized);
}

void	free_minishell(t_mini *mini)
{
	int	i;

	i = 0;
	while(mini->env->key[i])
	{
		free(mini->env->key[i]);
		free(mini->env->content[i]);
	}
	i = 0;
	while (mini->env->path[i])
	{
		free(mini->env->path[i]);
	}
}
