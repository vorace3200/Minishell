/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:27:04 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 14:56:08 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char	*remove_slash(const char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && str[i + 1] != '\\')
			i++;
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static void	handle_special_char(char c, int have_quote)
{
	if (c == 'n')
	{
		if (have_quote)
			write(1, "\\n", 2);
		else
			write(1, "n", 1);
	}
	else
		write(1, &c, 1);
}

static void	print_arg(char **args, int i, int have_quote)
{
	int		j;
	char	*arg;

	while (args[i])
	{
		arg = args[i];
		j = 0;
		while (arg[j])
		{
			if (arg[j] == '\\' && arg[j + 1])
			{
				j++;
				if (arg[j])
					handle_special_char(arg[j], have_quote);
			}
			else
				write(1, &arg[j], 1);
			j++;
		}
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	builtin_echo(t_shell *shell, char **args, int have_quote)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	print_arg(args, i, have_quote);
	if (newline)
		write(1, "\n", 1);
	shell->exit_status = 0;
}
