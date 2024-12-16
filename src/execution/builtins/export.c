/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:31:03 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/16 23:18:49 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

static int	parse_and_set_env(t_shell *shell, const char *arg)
{
	char	*name;
	char	*value;
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		name = ft_strndup(arg, eq - arg);
		value = ft_strdup(eq + 1);
	}
	else
	{
		name = ft_strdup(arg);
		value = ft_strdup("");
	}
	if (!name || !value || set_env_value(shell, name, value) != 0)
	{
		free(name);
		free(value);
		return (1);
	}
	free(name);
	free(value);
	return (0);
}

static char	**get_sorted_env(t_shell *shell)
{
	int		count;
	int		i;
	char	**sorted_env;

	count = env_count(shell->env);
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (shell->env[i])
	{
		sorted_env[i] = ft_strdup(shell->env[i]);
		if (!sorted_env[i])
		{
			while (--i >= 0)
				free(sorted_env[i]);
			free(sorted_env);
			return (NULL);
		}
		i++;
	}
	sorted_env[i] = NULL;
	sort_env_array(sorted_env);
	return (sorted_env);
}

static void	print_declared_env(char **env)
{
	int		i;
	char	*egal;

	i = 0;
	while (env[i])
	{
		egal = ft_strchr(env[i], '=');
		ft_putstr_fd("export ", 1);
		if (egal)
		{
			write(1, env[i], egal - env[i]);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(egal + 1, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			ft_putstr_fd(env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
}

static void	print_sorted_env(t_shell *shell)
{
	char	**sorted_env;

	sorted_env = get_sorted_env(shell);
	if (sorted_env)
	{
		print_declared_env(sorted_env);
		free_env_array(sorted_env);
	}
}

void	builtin_export(t_shell *shell, char **args)
{
	int	i;

	if (!args[1])
	{
		print_sorted_env(shell);
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell->exit_status = 1;
		}
		else if (parse_and_set_env(shell, args[i]) != 0)
			shell->exit_status = 1;
		else
			shell->exit_status = 0;
		i++;
	}
}
