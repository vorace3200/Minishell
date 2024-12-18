/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrunier <tbrunier@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:48:32 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/18 16:48:49 by tbrunier         ###   ########.fr       */
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
	cmd->invalid = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}
