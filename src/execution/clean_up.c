/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrunier <tbrunier@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 01:15:25 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 01:42:27 by tbrunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    cleanup_command(t_command *cmd)
{
    int i;

    if (!cmd)
        return ;
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
        {
            free(cmd->args[i]);
            i++;
        }
        free(cmd->args);
    }
    if (cmd->redir_in != -1)
        close(cmd->redir_in);
    if (cmd->redir_out != -1)
        close(cmd->redir_out);
}

void    cleanup_command_list(t_shell *shell)
{
    t_command *current;
    t_command *next;

    current = shell->cmd_list;
    while (current)
    {
        next = current->next;
        cleanup_command(current);
        free(current);
        current = next;
    }
    shell->cmd_list = NULL;
}