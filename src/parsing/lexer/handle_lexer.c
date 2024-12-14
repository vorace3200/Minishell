/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:20:42 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:22:41 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
}

int	handle_token(char **input, int *i, t_token **tokens, t_token **tail)
{
	int	result;

	skip_spaces(*input, i);
	if (!(*input)[*i])
		return (0);
	if (handle_pipe(*input, i, tokens, tail))
		return (1);
	if (handle_redirection(*input, i, tokens, tail))
		return (1);
	result = handle_quotes(input, i, tokens, tail);
	if (result == -1)
		return (-1);
	if (result == 1)
		return (1);
	handle_word(*input, i, tokens, tail);
	return (1);
}

t_token	*lexer(const char *input)
{
	t_token	*tokens;
	t_token	*tail;
	int		i;
	int		status;
	char	*input_copy;

	tokens = NULL;
	tail = NULL;
	i = 0;
	input_copy = ft_strdup(input);
	if (!input_copy)
		return (NULL);
	while (input_copy[i])
	{
		status = handle_token(&input_copy, &i, &tokens, &tail);
		if (status == -1)
		{
			free(input_copy);
			return (NULL);
		}
	}
	add_token(&tokens, &tail, create_token(NULL, TOKEN_EOF));
	free(input_copy);
	return (tokens);
}
