/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/03/15 17:07:52 by lle-pier         ###   ########.fr       */
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
	char	***args;
	char	**temp_args;
	int		pnum;
	int		i;

	if (argc != 1 || argv[0][0] == '\0')
		printf("ERROR\n");
	while (1)
	{
		printf("\033[1;36m");
		rl = readline("\033[1;36m<3\033[0;37m");
		pnum = 1;
		i = 0;
		while (rl[i])
		{
			if (rl[i] == '|')
				pnum++;
			i++;
		}
		temp_args = ft_split(rl, '|');
		i = 0;
		while (i < pnum)
		{
			args = malloc(sizeof(ft_strlen(temp_args[i])));
			args[i] = ft_split(temp_args[i], ' ');
			ft_printf("OK");
			ft_printf("%i : %s\n", i, args[i][1]);
			i++;
		}
		args = malloc(sizeof(ft_strlen(rl)));
		args[0] = ft_split(rl, ' ');
		//args[1] = ft_split(rl, ' ');
		main_exec(args, envp, pnum);
		add_history(rl);
	}
	return (0);
}
