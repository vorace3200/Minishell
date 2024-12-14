/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:34:03 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:22:28 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

static char	*create_env_var(const char *env_name, const char *value)
{
	int		len_name;
	int		len_value;
	char	*new_var;

	len_name = ft_strlen(env_name);
	len_value = ft_strlen(value);
	new_var = malloc(sizeof(char) * (len_name + len_value + 2));
	if (!new_var)
		return (NULL);
	ft_strncpy(new_var, env_name, len_name);
	new_var[len_name] = '=';
	ft_strncpy(new_var + len_name + 1, value, len_value + 1);
	return (new_var);
}

static int	add_to_env(t_shell *shell, char *new_var)
{
	int		size;
	char	**new_env;
	int		i;

	size = env_count(shell->env);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_var);
		return (1);
	}
	i = 0;
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

int	set_env_value(t_shell *shell, const char *env_name, const char *value)
{
	int		i;
	int		len;
	char	*new_var;

	if (!env_name || !*env_name)
		return (1);
	len = ft_strlen(env_name);
	new_var = create_env_var(env_name, value);
	if (!new_var)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], env_name, len)
			&& shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = new_var;
			return (0);
		}
		i++;
	}
	return (add_to_env(shell, new_var));
}
