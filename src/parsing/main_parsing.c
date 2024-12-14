/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:04:07 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:22:15 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	main_parsing(t_shell *shell)
{
	t_token	*tokens;

	if (!shell->input || *(shell->input) == '\0')
		return ;
	tokens = lexer(shell->input);
	if (!tokens)
	{
		shell->exit_status = MALLOC_ERROR;
		return ;
	}
	handle_command_list(tokens, shell);
	free_tokens(tokens);
}
