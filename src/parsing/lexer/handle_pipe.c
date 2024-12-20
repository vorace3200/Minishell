/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:01:26 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:22:43 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	handle_pipe(const char *input, int *i, t_token **tokens, t_token **tail)
{
	if (input[*i] == '|')
	{
		add_token(tokens, tail, create_token(ft_strdup("|"), TOKEN_PIPE));
		(*i)++;
		return (1);
	}
	return (0);
}
