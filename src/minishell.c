/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:25:44 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/14 17:49:23 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_mini		mini;
	t_list		*list;

	mini.env = create_list_env();
	init(&mini, __environ);
	while (1)
	{
		mini.in = STDIN_FILENO;
		mini.out = STDOUT_FILENO;
		list = create_list();
		get_input(&mini);
		get_redir(&mini);
		if (mini.io)
			for(int i = 0; mini.io[i]; i++)
				printf("%s -> \n", mini.io[i]);
		if(ft_strlen(mini.input) != 0)
		{
			if(split_cmd(&mini, list))
			{
				//run(&mini, list);
				//print_elements(list);
			}
			free_em_all(&mini, list);
		}
		else
			free(list);

	}
	free_minishell(&mini);
	return (0);
}
