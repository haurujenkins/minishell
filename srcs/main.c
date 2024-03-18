/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/03/18 10:26:20 by lle-pier         ###   ########.fr       */
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
	int		j;
	int		k;

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
		args = malloc(sizeof(ft_strlen(rl)));
		while (i < pnum)
		{
			args[i] = ft_split(temp_args[i], ' ');
			i++;
		}
		//args[0] = ft_split(rl, ' ');
		k = 0;
		while (k < pnum)
		{
			j = 0;
			while (args[k][j])
			{
				ft_printf("%i : %s\n", j, args[k][j]);
				j++;
			}
			ft_printf("\n");
			k++;
		}
		main_exec(args, envp, pnum);
		k = 0;
		while (k < pnum)
		{
			j = 0;
			while (args[k][j])
			{
				free(args[k][j]);
				j++;
			}
			k++;
		}
		add_history(rl);
	}
	return (0);
}
