/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:32:30 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/17 16:52:34 by vorace32         ###   ########.fr       */
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

char	*expand_variable(t_shell *shell, const char *arg, int *index)
{
	char	*var_name;
	char	*value;
	int		start;
	char	*env_val;

	(*index)++;
	var_name = get_var_name(&arg[*index], &start);
	*index += start;
	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
		value = ft_itoa(shell->exit_status);
	else
	{
		env_val = get_env_value(shell, var_name);
		if (!env_val)
			value = ft_strdup("");
		else
			value = ft_strdup(env_val);
	}
	if (!value)
		value = ft_strdup("");
	free(var_name);
	return (value);
}

char	*replace_var(t_shell *shell, const char *arg)
{
	char	*result;
	char	*expanded_value;
	int		i;
	char	tmp[2];

	result = ft_strdup("");
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && (ft_isalnum(arg[i + 1]) || arg[i
					+ 1] == '_' || arg[i + 1] == '?'))
		{
			expanded_value = expand_variable(shell, arg, &i);
			result = ft_strjoin_free(result, expanded_value);
			free(expanded_value);
		}
		else
		{
			tmp[0] = arg[i++];
			tmp[1] = '\0';
			result = ft_strjoin_free(result, tmp);
		}
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
