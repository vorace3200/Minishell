/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:32:30 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 00:18:26 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

char	*get_var_name(const char *str, int *len)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (NULL);
	if (str[i] == '?')
	{
		*len = 1;
		return (ft_strdup("?"));
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*len = i;
	return (ft_strndup(str, i));
}

char	*replace_var(t_shell *shell, const char *arg)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (!process_char(shell, arg, &i, &result))
			continue ;
		i++;
	}
	return (result);
}

void	expand_variables(t_shell *shell)
{
	t_command	*cmd;
	int			i;
	char		*expanded;

	cmd = shell->cmd_list;
	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			expanded = replace_var(shell, cmd->args[i]);
			free(cmd->args[i]);
			cmd->args[i] = expanded;
			i++;
		}
		cmd = cmd->next;
	}
}
