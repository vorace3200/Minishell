/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:59:17 by vorace32          #+#    #+#             */
/*   Updated: 2024/11/04 15:18:12 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell_exec.h"

int	handle_redirection(const char *input, int *i, t_token **tokens,
		t_token **tail)
{
	char			op;
	t_token_type	type;
	char			*op_str;

	if (input[*i] == '>' || input[*i] == '<')
	{
		op = input[(*i)++];
		if (op == '>')
			type = TOKEN_REDIR_OUT;
		else
			type = TOKEN_REDIR_IN;
		if (input[*i] == op)
		{
			(*i)++;
			if (op == '>')
				type = TOKEN_D_REDIR_OUT;
			else
				type = TOKEN_D_REDIR_IN;
		}
		op_str = ft_strndup(&op, 1);
		add_token(tokens, tail, create_token(op_str, type));
		return (1);
	}
	return (0);
}
