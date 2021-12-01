/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:58:06 by paugusto          #+#    #+#             */
/*   Updated: 2021/11/30 21:55:01 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	how_many_words(char *str)
{
	static int	i;
	int	words;
	int	s_quotes;
	int	d_quotes;

	s_quotes = 0;
	d_quotes = 0;
	if(!i)
		i = 0;
	else if (str[i] == '\0')
		return (0);
	else
		i++;
	words = 0;
	while (str[i] != '|' && str[i] != '\0')
	{
		if(str[i] == 34 && d_quotes == 1)
		{
			d_quotes = 0;
			words++;
		}
		else if(str[i] == 34 && s_quotes == 0)
			d_quotes = 1;
		if(str[i] == 39 && s_quotes == 1)
		{
			s_quotes = 0;
			words++;
		}
		else if(str[i] == 39 && d_quotes == 0)
			s_quotes = 1;
		if(str[i] == ' ' && str[i - 1] != ' ' && str[i - 1] != '|'
			&& s_quotes == 0 && d_quotes == 0)
			words++;
		i++;
	}
	if (str[i] == '\0')
		words++;
	return (words);
}

void	how_many_pipes(t_mini *mini)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (mini->input[i])
	{
		if (mini->input[i] == '|')
			pipes++;
		i++;
	}
	mini->pipes = pipes;
}

void	process_input(t_mini *mini)
{
	char	*aux;
	int		i;
	int		j;

	aux = ft_strtrim(mini->input, " ");
	mini->input_parsed = malloc((mini->pipes + 1) * sizeof(char **));
	i = 0;
	while (i <= mini->pipes)
	{
		input_parsed[i] = malloc(sizeof(char *) * how_many_words(aux) + 1);
		input_parsed[i] = ft_split()
		i++;
	}
}

void	get_input(t_mini *mini)
{
	mini->input = readline(">> ");
	if (ft_strlen(mini->input) != 0)
		add_history(mini->input);
}


// input_parsed =
// {
// 	parse1
// 	{
// 		"Pedro",
// 		"Augusto",
// 		"Dias"
// 	},
// 	parse2
// 	{
// 		"Igor",
// 		"Vaz",
// 		"Ferndes"
// 	},
// 	parse3
// 	{
// 		"minishell",
// 		"é",
// 		"uma",
// 		"bosta"
// 	}
// }

// input_parsed = malloc((pipes + 1) * sizeof(char **) + 1) //2
// while (i <= mini->pipes)
// {

// }
// input_parsed[i] = '\0';

// //Pedro Augusto | igor vaz | odeio shell
// ft_split(string, "|") = Pedro Augusto, Igor Vaz, Odeio Shell
// input_parsed[i][j] = Pedro



