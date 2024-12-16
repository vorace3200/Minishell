/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:44:22 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/16 23:37:28 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static void	init_args(t_command *cmd)
{
	cmd->args_size = 2;
	cmd->args = malloc(sizeof(char *) * cmd->args_size);
	if (!cmd->args)
	{
		ft_putstr_fd("Error: memory allocation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	cmd->args_count = 0;
}

static void	resize_args(t_command *cmd)
{
	int		new_size;
	char	**new_args;
	int		i;

	new_size = cmd->args_size * 2;
	new_args = malloc(sizeof(char *) * new_size);
	if (!new_args)
	{
		ft_putstr_fd("[ERROR] Failed to allocate memory.\n", 2);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < cmd->args_count)
		new_args[i] = cmd->args[i];
	free(cmd->args);
	cmd->args = new_args;
	cmd->args_size = new_size;
}

void	add_argument_to_command(t_command *cmd, char *arg)
{
	if (!cmd->args)
		init_args(cmd);
	if (cmd->args_count >= cmd->args_size - 1)
		resize_args(cmd);
	cmd->args[cmd->args_count++] = ft_strdup(arg);
	cmd->args[cmd->args_count] = NULL;
}

void	add_redirection_to_command(t_command *cmd, t_token_type type,
		char *file)
{
	if (type == TOKEN_REDIR_IN)
		handle_input_redir(cmd, file);
	else if (type == TOKEN_REDIR_OUT)
		handle_output_redir(cmd, file, 0);
	else if (type == TOKEN_D_REDIR_OUT)
		handle_output_redir(cmd, file, 1);
	else if (type == TOKEN_D_REDIR_IN)
		handle_heredoc(cmd, file);
}
