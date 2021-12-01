/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:58:06 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/01 20:43:28 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*is_quotes(int *quotes)
{
	
}

int	is_valid(char c, int d_quotes, int s_quotes)
{
	int	valid;

	if(!c)
	{
		valid = 0;
		return (valid);
	}
	if (((c != '|' && c != '<' && c != '>' ) && d_quotes == 0 && s_quotes == 0)
		|| ((c == '|' || c == '<' || c == '>' )
		&& (d_quotes == 1 || s_quotes == 1)))
		valid = 1;
	else
		valid = 0;
	return (valid);
}

/*
** quotes[0] -> double quotes
** quotes[1] -> single quotes
*/
int	how_many_words(char *str, t_mini *mini)
{
	static int	i;
	int	words;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	if(!i)
		i = 0;
	else if (str[i] == '\0')
		return (0);
	else
		i++;
	words = 0;
	while (is_valid(str[i], quotes[0], quotes[1]))
	{

	}
	return (words);
}

void	process_input(t_mini *mini)
{
	char	*aux;
	int		i;
	int		j;

	aux = ft_strtrim(mini->input, " ");
	mini->input_parsed = malloc((mini->n_pipes + 1) * sizeof(char **));
	i = 0;
	while (i <= mini->n_pipes)
	{
		mini->input_parsed[i] = malloc(sizeof(char *) * how_many_words(aux, mini) + 1);
		i++;
	}
	if (mini->is_quotes_closed = 0)
	{
		//free em tudo, fecha tudo.
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



