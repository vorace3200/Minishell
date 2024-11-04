/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:47:29 by vorace32          #+#    #+#             */
/*   Updated: 2024/11/04 15:36:12 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell_exec.h"

static t_command	*initialize_command(t_command **last_cmd, t_shell *shell)
{
	t_command	*new_cmd;

	new_cmd = new_command_node();
	if (!new_cmd)
		return (NULL);
	if (!shell->cmd_list)
		shell->cmd_list = new_cmd;
	if (*last_cmd)
	{
		(*last_cmd)->next = new_cmd;
		new_cmd->prev = *last_cmd;
	}
	return (new_cmd);
}

static int	handle_pipe_token(t_command **current_cmd, t_command **last_cmd,
		t_shell *shell)
{
	if (!*current_cmd)
	{
		ft_putstr_fd("Syntax error near unexpected token '|'\n", 2);
		shell->exit_status = ERROR;
		return (-1);
	}
	(*current_cmd)->pipe_out = 1;
	*last_cmd = *current_cmd;
	*current_cmd = NULL;
	return (0);
}

static int	handle_redirection_token(t_command **current_cmd, t_token **token,
		t_command **last_cmd, t_shell *shell)
{
	if (!*current_cmd)
	{
		*current_cmd = initialize_command(last_cmd, shell);
		if (!*current_cmd)
			return (-1);
	}
	*token = (*token)->next;
	if (!*token || (*token)->type != TOKEN_WORD)
	{
		ft_putstr_fd("Syntax error: expected file after redirection\n", 2);
		shell->exit_status = ERROR;
		return (-1);
	}
	add_redirection_to_command(*current_cmd, (*token)->prev->type,
		(*token)->value);
	return (0);
}

static int	process_token(t_token **token, t_command **current_cmd,
		t_command **last_cmd, t_shell *shell)
{
	if ((*token)->type == TOKEN_WORD)
	{
		if (!*current_cmd)
		{
			*current_cmd = initialize_command(last_cmd, shell);
			if (!*current_cmd)
				return (-1);
		}
		add_argument_to_command(*current_cmd, (*token)->value);
	}
	else if ((*token)->type == TOKEN_PIPE)
		return (handle_pipe_token(current_cmd, last_cmd, shell));
	else if ((*token)->type == TOKEN_REDIR_IN
		|| (*token)->type == TOKEN_REDIR_OUT
		|| (*token)->type == TOKEN_D_REDIR_IN
		|| (*token)->type == TOKEN_D_REDIR_OUT)
		return (handle_redirection_token(current_cmd, token, last_cmd, shell));
	else
	{
		ft_putstr_fd("Error: unknown token\n", 2);
		shell->exit_status = ERROR;
		return (-1);
	}
	return (0);
}

void	handle_command_list(t_token *tokens, t_shell *shell)
{
	t_command	*current_cmd;
	t_command	*last_cmd;
	t_token		*token;

	current_cmd = NULL;
	last_cmd = NULL;
	token = tokens;
	while (token && token->type != TOKEN_EOF)
	{
		if (process_token(&token, &current_cmd, &last_cmd, shell) == -1)
			return ;
		token = token->next;
	}
}
