/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:50:24 by vorace32          #+#    #+#             */
/*   Updated: 2024/11/04 15:17:43 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell_exec.h"

void	handle_word(const char *input, int *i, t_token **tokens, t_token **tail)
{
	int		start;
	char	*value;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '>' && input[*i] != '<' && input[*i] != '\''
		&& input[*i] != '\"')
		(*i)++;
	value = ft_strndup(input + start, *i - start);
	add_token(tokens, tail, create_token(value, TOKEN_WORD));
}
