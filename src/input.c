/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvaz-fe <igvaz-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:58:06 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/02 02:13:43 by igvaz-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** ASCII Table
** double quotes -> 34
** single quotes -> 39
*/
int	check_quotes(char c)
{
	static int	d_quotes;
	static int	s_quotes;

	if (!d_quotes)
		d_quotes = 0;
	if (!s_quotes)
		s_quotes = 0;
	if (c == 34 && d_quotes == 1)
		d_quotes = 0;
	else if (c == 34 && s_quotes == 0)
		d_quotes = 1;
	if (c == 39 && s_quotes == 1)
		s_quotes = 0;
	else if (c == 39 && d_quotes == 0)
		s_quotes = 1;
	if (s_quotes == 1 || d_quotes == 1)
		return (1);
	else
		return (0);
}

int	is_condition_valid(char c, int quotes)
{
	int	valid;

	if (!c)
	{
		valid = 0;
		return (valid);
	}
	if (((c != '|' && c != '<' && c != '>' ) && quotes == 0)
		|| ((c == '|' || c == '<' || c == '>' ) && quotes == 1))
		valid = 1;
	else
		valid = 0;
	return (valid);
}

int	is_word_valid(char *str, int i, int quotes)
{
	int	word;

	word = 0;
	if ((str[i] == ' ' || str[i] == '|' || str[i] == '<' || str[i] == '>')
		&& str[i - 1] != ' ' && str[i - 1] != '|'
		&& str[i - 1] != '>' && str[i - 1] != '<'
		&& quotes == 0)
		word++;
	return (word);
}

void	redirects_counter(char *str, int i, t_mini *mini)
{
	if (str[i] == '|')
		mini->n_pipes += 1;
	else if (str[i] == '>' && str[i - 1] == '>')
		mini->n_rhere_docs += 1;
	else if (str[i] == '<' && str[i - 1] == '<')
		mini->n_lhere_docs += 1;
	else if (str[i] == '>' && str[i + 1] != '>')
		mini->n_rredirects += 1;
	else if (str[i] == '<' && str[i + 1] != '<')
		mini->n_rredirects += 1;
}

/*
** quotes[0] -> double quotes
** quotes[1] -> single quotes
*/
int	how_many_words(char *str, t_mini *mini)
{
	static int	i;
	int			words;
	int			quotes;

	quotes = 0;
	if (!i)
		i = 0;
	else if (str[i] == '\0')
		return (0);
	else
		i++;
	words = 0;
	while (is_condition_valid(str[i], quotes))
	{
		quotes = check_quotes(str[i]);
		words += is_word_valid(str, i, quotes);
		i++;
	}
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		redirects_counter(str, i, mini);
	if (str[i] == '\0' && str[i - 1] != ' ' && str[i - 1] != '|'
		&& str[i - 1] != '<' && str[i - 1] != '>')
		words++;
	return (words);
}

void	process_input(t_mini *mini)
{
	char	*aux;
	int		i;

	aux = ft_strtrim(mini->input, " ");
	mini->input_parsed = malloc((mini->n_pipes + 1) * sizeof(char **));
	i = 0;
	while (i <= mini->n_pipes)
	{
		printf("%d", how_many_words(aux, mini));
		// mini->input_parsed[i] = malloc(sizeof(char *) * how_many_words(aux, mini) + 1);
		i++;
	}
	if (mini->is_quotes_closed == 0)
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
