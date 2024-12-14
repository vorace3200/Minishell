/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:48:32 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:22:32 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

t_command	*new_command_node(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->args_size = 0;
	cmd->args_count = 0;
	cmd->cmd_path = NULL;
	cmd->pipe_in = 0;
	cmd->pipe_out = 0;
	cmd->pipe_in_fd = -1;
	cmd->pipe_out_fd = -1;
	cmd->redir_in = -1;
	cmd->redir_out = -1;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}
