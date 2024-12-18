/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:27:04 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/18 16:51:28 by vorace32         ###   ########.fr       */
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

static void	print_arg(char **args, int i)
{
	char	*str;

	while (args[i])
	{
		str = remove_slash(args[i]);
		if (str)
		{
			printf("%s", str);
			free(str);
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

void	builtin_echo(t_shell *shell, char **args)
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
	print_arg(args, i);
	if (newline)
		printf("\n");
	else
		printf("%%\n");
	shell->exit_status = 0;
}
