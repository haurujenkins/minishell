/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/06/03 17:08:34 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_data	da;

	if (argc != 1 || argv[0][0] == '\0')
		printf("ERROR\n");
	set_all(&da, envp, 0);
	set_parse(&da);
	while (1)
	{
		da.freed = 0;
		if_sig(&da);
		rl = readline("\001\033[1;36m\002<3 \001\033[0;37m\002");
		if (g_stop_execution == 1)
			stop_g_exec(&da);
		if (!rl)
		{
			if_not_rl(&da);
			break ;
		}
		rl_ok(rl, &da, envp);
		free(rl);
	}
	return (0);
}
