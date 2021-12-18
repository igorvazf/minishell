/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:41:53 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/18 17:59:31 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	is_in_quote(char c)
// {

// 	if (c == S_QUOTE)
// 	{
// 		if (mini->is_open_s == 0 && mini->is_open_d == 0)
// 			mini->is_open_s = 1;
// 		else if (mini->is_open_s == 1)
// 			mini->is_open_s = 0;
// 	}
// 	if (c == D_QUOTE)
// 	{
// 		if (mini->is_open_d == 0 && mini->is_open_s == 0)
// 			mini->is_open_d = 1;
// 		else if (mini->is_open_d == 1)
// 			mini->is_open_d = 0;
// 	}
// }

char	*put_spaces(char *str, int len, int i, int j)
{
	char	*input;

	input = malloc(sizeof(char) * len + 1);
	while (str[i])
	{
		while (str[i] == '<' || str[i] == '>')
			input[j++] = str[i++];
		if (str[i] != ' ' && (str[i + 1] == '|' || str[i + 1] == '<' || str[i + 1] == '>'))
		{
			input[j++] = str[i++];
			input[j++] = ' ';
			input[j++] = str[i++];
		}
		while (str[i] == '<' || str[i] == '>')
			input[j++] = str[i++];
		if (str[i] == '|' && str[i + 1] != ' ' && str[i + 1] != '\0')
		{
			input[j++] = '|';
			input[j++] = ' ';
			i++;
		}
		if (str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '\0')
			input[j++] = str[i++];
		else
			i++;
	}
	input[j] = '\0';
	return (input);
}

int	correct_len(char	*str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] == '<' || str[i] == '>')
		{
			len++;
			i++;
		}
		if (str[i] != ' ' && (str[i + 1] == '|' || str[i + 1] == '<' || str[i + 1] == '>'))
		{
			len += 3;
			i++;
		}
		while (str[i] == '<' || str[i] == '>')
		{
			len++;
			i++;
		}
		if (str[i] == '|' && str[i + 1] != ' ' && str[i + 1] != '\0')
		{
			len += 2;
			i++;
		}
		if (str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '\0')
		{
			len++;
			i++;
		}
		else
			i++;
	}
	return (len);
}

void	input_sanitizer(t_mini *mini)
{
	char	*aux;
	int		len;

	aux = ft_strtrim(mini->input, " ");
	len = correct_len(aux);
	mini->input_sanitized = put_spaces(aux, len, 0, 0);
	free(aux);
}
