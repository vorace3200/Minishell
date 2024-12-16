/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_direction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:33:02 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/16 23:40:39 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	handle_input_redir(t_command *cmd, char *file)
{
	if (cmd->redir_in != -1)
		close(cmd->redir_in);
	cmd->redir_in = open(file, O_RDONLY);
	if (cmd->redir_in < 0)
		ft_putstr_fd("[ERROR] Failed to open input file.\n", 2);
}

void	handle_output_redir(t_command *cmd, char *file, int append)
{
	int	flags;

	if (cmd->redir_out != -1)
		close(cmd->redir_out);
	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	cmd->redir_out = open(file, flags, 0644);
	if (cmd->redir_out < 0)
		ft_putstr_fd("[ERROR] Failed to open output file.\n", 2);
}
