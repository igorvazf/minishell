/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:54:03 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/12 16:36:41 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_em_all(t_mini *mini, t_list *list)
{
	destroy_list(list);
	free(mini->input);
	free(mini->input_sanitized);
	if (mini->correct_path != NULL)
		free(mini->correct_path);
	if (mini->io != NULL)
		minifree(mini->io);
}

void	free_minishell(t_mini *mini)
{
	destroy_list_env(mini->env);
	minifree(mini->path);
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

/*
** Function that destroy (and free all) a double linked list
*/
void	destroy_list(t_list *list)
{
	t_node	*node;
	t_node	*aux;

	node = list->begin;
	while (node->next != NULL)
	{
		minifree(node->str);
		aux = node;
		node = node->next;
		free(aux);
	}
	minifree(node->str);
	free(node);
	free(list);
	list = NULL;
}

void	destroy_list_env(t_list_env *list)
{
	t_node_env	*node;
	t_node_env	*aux;

	node = list->begin;
	while (node->next != NULL)
	{
		free(node->key);
		free(node->content);
		aux = node;
		node = node->next;
		free(aux);
	}
	free(node->key);
	free(node->content);
	free(node);
	free(list);
	list = NULL;
}
