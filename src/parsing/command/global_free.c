/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:42:35 by vorace32          #+#    #+#             */
/*   Updated: 2024/11/04 15:37:13 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell_exec.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_commands(t_command *cmd_list)
{
	t_command	*tmp;
	int			i;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		i = 0;
		while (tmp->args && tmp->args[i])
		{
			free(tmp->args[i]);
			i++;
		}
		free(tmp->args);
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->redir_in != -1)
			close(tmp->redir_in);
		if (tmp->redir_out != -1)
			close(tmp->redir_out);
		free(tmp);
	}
}
