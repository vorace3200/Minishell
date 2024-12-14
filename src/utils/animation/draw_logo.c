/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_logo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:42:31 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 15:02:39 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static void	print_banner_part1(void)
{
	printf("╔═══════                                         "
		"                ══════╗\n");
	printf("║                                                          "
		"            ║     \n");
	printf("║  %s███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗"
		"     ██╗%s      ║\n", YELLOW, WHITE);
	printf("║  %s████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║"
		"     ██║%s      ║\n", YELLOW, WHITE);
	printf("   %s██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║"
		"     ██║%s       \n", YELLOW, WHITE);
}

static void	print_banner_part2(void)
{
	printf("   %s██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║"
		"     ██║%s       \n", YELLOW, WHITE);
	printf("   %s██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗"
		"███████╗%s  \n", YELLOW, WHITE);
	printf("   %s╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝"
		"╚══════╝%s  \n", YELLOW, WHITE);
}

static void	print_banner_part3(void)
{
	printf("                                                           "
		"             \n");
	printf("║                       %sWelcome to Minishell v1.0         "
		"    %s         ║ \n", CYAN, WHITE);
	printf("║                  %sPress %sCtrl+D %sor %stype 'exit'"
		"%s to %squit %s                ║\n", BLUE, YELLOW, BLUE,
		YELLOW, BLUE, RED, WHITE);
	printf("║                                                          "
		"            ║\n");
	printf("╚═══════                                             "
		"           ═══════╝\n");
}

void	draw_logo(void)
{
	printf("\033[2J\033[H");
	printf("%s%s", WHITE, BOLD);
	print_banner_part1();
	print_banner_part2();
	print_banner_part3();
	printf("%s\n", RESET);
}
