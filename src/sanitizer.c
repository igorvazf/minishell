int	how_many_words(char *str, t_mini *mini)
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
	while (((str[i] != '|' && d_quotes = 0 && s_quotes = 0)
			|| (str[i] == '|' && (d_quotes = 1 || s_quotes = 1)))
			&& str[i] != '\0')
	{
		if(str[i] == 34 && d_quotes == 1)
		{
			d_quotes = 0;
			mini->is_quotes_closed = 1;
			words++;
		}
		else if(str[i] == 34 && s_quotes == 0)
		{
			d_quotes = 1;
			mini->is_quotes_closed = 0;
		}
		if(str[i] == 39 && s_quotes == 1)
		{
			s_quotes = 0;
			mini->is_quotes_closed = 1;
			words++;
		}
		else if(str[i] == 39 && d_quotes == 0)
		{
			s_quotes = 1;
			mini->is_quotes_closed = 0;
		}
		if(str[i] == ' ' && str[i - 1] != ' ' && str[i - 1] != '|'
			&& s_quotes == 0 && d_quotes == 0)
			words++;
		i++;
	}
	if (str[i] == '\0' && d_quotes == 0 && s_quotes == 0)
		words++;
	return (words);
}
