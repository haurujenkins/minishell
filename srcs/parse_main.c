/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/06/05 17:18:32 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_data	da;

	if (argc != 1 || argv[0][0] == '\0')
		return (write(2, "ERROR : no arguments required\n", 31));
	set_all(&da, envp, 0);
	while (1)
	{
		set_parse(&da);
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
	rl_clear_history();
	return (0);
}
