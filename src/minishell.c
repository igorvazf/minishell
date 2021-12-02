/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvaz-fe <igvaz-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:25:44 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/02 01:36:23 by igvaz-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_mini	mini;

	init(&mini);
	while (1)
	{
		get_input(&mini);
		process_input(&mini);
		//execute_cmd(&mini, mini.input_parsed[0]);
		free(mini.input);
	}
	return (0);
}
