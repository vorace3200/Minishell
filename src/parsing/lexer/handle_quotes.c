/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:51:26 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 14:56:59 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char	*read_more_input(char quote)
{
	char	*line;
	char	*prompt;

	if (quote == '\'')
		prompt = "quote> ";
	else
		prompt = "dquote> ";
	line = readline(prompt);
	if (!line)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for `", 2);
		ft_putstr_fd(&quote, 2);
		ft_putstr_fd("'\n", 2);
		return (NULL);
	}
	return (line);
}

int	read_until_closing_quote(char **input, int *i, char quote)
{
	char	*new_input;
	char	*temp_input;
	char	*combined_input;

	while ((*input)[*i] && (*input)[*i] != quote)
		(*i)++;
	while ((*input)[*i] != quote)
	{
		new_input = read_more_input(quote);
		if (!new_input)
			return (-1);
		temp_input = ft_strjoin(*input, "\n");
		if (!temp_input)
			return (-1);
		combined_input = ft_strjoin_free(temp_input, new_input);
		if (!combined_input)
			return (-1);
		free(*input);
		*input = combined_input;
		free(new_input);
		while ((*input)[*i] && (*input)[*i] != quote)
			(*i)++;
	}
	return (0);
}

static char	*wrap_with_quotes(char *value, char quote)
{
	char	*tmp;
	char	*final;

	if (quote != '\'')
		return (value);
	tmp = ft_strjoin("'", value);
	free(value);
	final = ft_strjoin_free(tmp, "'");
	return (final);
}

int	handle_quotes(char **input, int *i, t_token **tokens, t_token **tail)
{
	char	quote;
	int		start;
	char	*value;
	t_token	*new_token;

	if ((*input)[*i] != '\'' && (*input)[*i] != '"')
		return (0);
	quote = (*input)[(*i)++];
	start = *i;
	if (read_until_closing_quote(input, i, quote) == -1)
		return (-1);
	value = ft_strndup(*input + start, *i - start);
	(*i)++;
	if (!value || !*value)
	{
		free(value);
		return (1);
	}
	value = wrap_with_quotes(value, quote);
	new_token = create_token(value, TOKEN_WORD);
	new_token->was_double_quoted = 1;
	add_token(tokens, tail, new_token);
	return (1);
}
