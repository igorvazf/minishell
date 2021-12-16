/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:25:44 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/16 23:30:29 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_input(t_mini *mini)
{
	//signals(1);
	mini->input = readline(">> ");
	if (ft_strlen(mini->input) != 0)
		add_history(mini->input);
	input_sanitizer(mini);
}

int	main(void)
{
	t_mini	mini;
	t_list	*list;

	init(&mini, __environ);
	//print_env(mini.env);
	
	while (1)
	{
	// // 	mini.in = STDIN_FILENO;
	// // 	mini.out = STDOUT_FILENO;
		list = create_list();
		get_input(&mini);
		get_redir(&mini);
		// if (mini.io)
		// 	for(int i = 0; mini.io[i]; i++)
		// 		printf("%s -> \n", mini.io[i]);
		if(ft_strlen(mini.input) != 0)
		{
			if (!ft_strcmp(mini.input, "exit"))
				miniexit(&mini, list);
			push_node(list, mini.input);
			if(split_cmd(&mini, list))
			{
				execute(&mini, list, list->begin);
				//print_elements(list);
			}
			free_reset(&mini, list);
		}
		else
			free_list(&list);
	}
	free_em_all(&mini);

	

	// list = create_list();

	// push_node(list, "Pedro Augusto Dias");
	// push_node(list, "igor Fernandes Vaz");
	// push_node(list, "Nathalia Ritter Rosa");
	// print_elements(list);
	// free_list(&list);
	return (0);
}