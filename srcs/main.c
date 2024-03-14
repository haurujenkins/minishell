/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/03/14 16:26:08 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	char	**args;

	if (argc != 1 || argv[0][0] == '\0')
		printf("ERROR\n");
	while (1)
	{
		printf("\033[1;36m");
		rl = readline("$> ");
		args = ft_split(rl, '|');
		main_exec(args, envp);
		add_history(rl);
	}
	return (0);
}
