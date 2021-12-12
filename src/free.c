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
	destroy_list(list);
	free(mini->input);
	free(mini->input_sanitized);
	free(mini->correct_path);
	if (mini->io)
		minifree(mini->io);
}

void	free_minishell(t_mini *mini)
{
	minifree(mini->env->key);
	minifree(mini->env->path);
	minifree(mini->env->content);
}

void	minifree(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
}
