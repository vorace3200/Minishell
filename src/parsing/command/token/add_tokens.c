/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:27:29 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:22:37 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

void	add_token(t_token **head, t_token **tail, t_token *new_token)
{
	if (!*head)
		*head = new_token;
	else
		(*tail)->next = new_token;
	*tail = new_token;
}
