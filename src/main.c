/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:25:44 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/19 18:37:38 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_input(t_mini *mini, t_sani *sani)
{
	//signals(1);
	mini->input = readline(">> ");
	if (ft_strlen(mini->input) != 0)
		add_history(mini->input);
	input_sanitizer(mini, sani);
}

int	main(void)
{
	t_mini	mini;
	t_list	*list;
	t_sani	sani;

	init(&mini, __environ);
	//print_env(mini.env);
	while (1)
	{
		mini.in = STDIN_FILENO;
		mini.out = STDOUT_FILENO;
		list = create_list();
		get_input(&mini, &sani);
		//printf("%s\n", mini.input_sanitized);
		if(ft_strlen(mini.input) != 0 && mini.input[0] != '|')
		{
			if (!ft_strcmp(mini.input, "exit"))
				miniexit(&mini, list);
			if(split_cmd(&mini, list))
			{
				run(&mini, list);
			}
		}
		free_reset(&mini, list);
	}
	free_em_all(&mini);
	return (0);
}
