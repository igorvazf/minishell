/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:35:22 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/29 21:40:26 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minicd(t_mini *mini, t_node *node)
{
	t_nodenv	*env;
	char		*home;
	int			is_error;

	env = mini->env->begin;
	home = NULL;
	is_error = 0;
	if (node->str[1])
		is_error = chdir(node->str[1]);
	else
	{
		while (env != NULL)
		{
			if (!ft_strcmp(env->key, "HOME"))
				home = ft_strdup(env->content);
			env = env->next;
		}
		if (home != NULL)
		{
			chdir(home);
			free(home);
		}
	}
	if (is_error < 0)
		printf("cd: no such file or directory\n");
}
