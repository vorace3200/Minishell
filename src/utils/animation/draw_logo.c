/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_logo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:42:31 by vorace32          #+#    #+#             */
/*   Updated: 2024/10/30 02:23:46 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell_exec.h"

static void	print_banner_part1(void)
{
	printf("╔══════════════════════════════════════════════════════════"
		"════╗\n");
	printf("║                                                          "
		"    ║     \n");
	printf("║  %s███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗%s"
		"      ║\n", YELLOW, BLUE);
	printf("║  %s████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║%s"
		"      ║\n", YELLOW, BLUE);
	printf("║  %s██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║%s"
		"      ║\n", YELLOW, BLUE);
}

static void	print_banner_part2(void)
{
	printf("║  %s██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║%s"
		"      ║\n", YELLOW, BLUE);
	printf("║  %s██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███"
		"████╗%s ║\n", YELLOW, BLUE);
	printf("║  %s╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══"
		"════╝%s ║\n", YELLOW, BLUE);
}

static void	print_banner_part3(void)
{
	printf("║                                                          "
		"    ║\n");
	printf("║                  %sWelcome to Minishell v1.0               "
		"    %s║\n", CYAN, BLUE);
	printf("║              Press %sCtrl+D %sor %stype 'exit'"
		"%s to quit %s            ║\n", YELLOW, BLUE, YELLOW, RED, BLUE);
	printf("║                                                          "
		"    ║\n");
	printf("╚══════════════════════════════════════════════════════════"
		"════╝\n");
}

void	draw_logo(void)
{
	printf("\033[2J\033[H");
	printf("%s%s", BLUE, BOLD);
	print_banner_part1();
	print_banner_part2();
	print_banner_part3();
	printf("%s\n", RESET);
}
