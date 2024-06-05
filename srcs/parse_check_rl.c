/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_rl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:34:31 by abolea            #+#    #+#             */
/*   Updated: 2024/06/05 17:16:03 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_not_rl(t_data *da)
{
	int	i;

	write(1, "exit\n", 5);
	i = -1;
	while (da->my_env[++i] != NULL)
		free(da->my_env[i]);
	free(da->my_env);
}

void	if_error_pipe(t_data *da)
{
	da->exit_status = 2;
	da->parse_error = 1;
	write(2, "too many pipes\n", 15);
}

void	if_error(t_data *da)
{
	da->exit_status = 2;
	da->parse_error = 1;
	write(2, "Syntax error\n", 13);
}

void	stop_g_exec(t_data *da)
{
	g_stop_execution = 0;
	da->exit_status = 130;
}

void	rl_ok(char *rl, t_data *da, char **envp)
{
	if (check_error(rl))
	{
		if_error(da);
		add_history(rl);
		return;
	}
	if (rl[0])
		add_history(rl);
	if (nb_pipe(rl) == -1)
		if_error_pipe(da);
	if (rl && *rl != '\0' && da->parse_error != 1)
		if_rl(rl, da, envp);
	da->parse_error = 0;
}

void	if_sig(t_data *da)
{
	da->freed = 0;
	signal(SIGINT, sigint_handler_main);
	signal(SIGQUIT, SIG_IGN);
	if (g_stop_execution == 1)
	{
		g_stop_execution = 0;
		da->exit_status = 130;
	}
}
