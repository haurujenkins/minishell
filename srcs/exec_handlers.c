/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:01:40 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/24 19:06:23 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler_child(int signum)
{
	(void)signum;
	printf("\n");
	stop_execution = 1;
}

void	sigquit_handler_child(int signum)
{
	(void)signum;
	printf("Quit (core dumped)\n");
	stop_execution = 2;
}

void	sigint_handler_main(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	stop_execution = 1;
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "^C\n", 3);
	stop_execution = 1;
	rl_done = 1;
}

void	sigquit_handler_doc(t_data *da)
{
	da->mysignal.nb_delim--;
	printf("bash: warning: here-document delimited by end-of-file \
	(wanted `%s')\n", da->mysignal.endof);
	if (da->mysignal.nb_delim != 0)
		return ;
	da->mysignal.exit = 1;
}
