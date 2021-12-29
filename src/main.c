/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:25:44 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/28 21:03:37 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char	**environ;

int	main(void)
{
	t_mini	mini;
	t_list	*list;
	t_sani	sani;

	init(&mini, environ);
	while (1)
	{
		mini.in = STDIN_FILENO;
		mini.out = STDOUT_FILENO;
		list = create_list();
		get_input(&mini, &sani);
		if (ft_strlen(mini.input) != 0 && mini.input[0] != '|')
		{
			if (!ft_strcmp(mini.input, "exit"))
				miniexit(&mini, list);
			if (split_cmd(&mini, list) && validade(list))
				run(&mini, list);
		}
		free_reset(&mini, list);
		mini.pipe = 0;
	}
	free_em_all(&mini);
	return (0);
}
