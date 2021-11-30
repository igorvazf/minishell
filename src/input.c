/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:58:06 by paugusto          #+#    #+#             */
/*   Updated: 2021/11/30 19:15:22 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_input(t_mini *mini)
{
	char	*aux;
	int		i;

	aux = ft_strtrim(mini->input, " ");
	mini->input_parsed = ft_split(aux, ' ');
}

void	get_input(t_mini *mini)
{
	mini->input = readline(">> ");
	if (ft_strlen(mini->input) != 0)
		add_history(mini->input);
}
