/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:30:54 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/30 15:42:39 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data(t_data *da, char **envp)
{
	// close(da->pipefd[0]);
	// close(da->pipefd[1]);
	close(da->fd_input);
	close(da->fd_output);
	da->i = -1;
	if (!(da->cmd1 == NULL))
	{
		while (da->cmd1[++da->i])
			free(da->cmd1[da->i]);
		free (da->cmd1);
	}
	da->i = -1;
	if (!(envp[0] == NULL))
	{
		while (da->my_path[++da->i])
			free(da->my_path[da->i]);
		free(da->my_path);
	}
	if (da->cmd != NULL)
		free(da->cmd);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_double_tab(char ***tab, t_data *da)
{
	int	i;
	int	j;

	i = 0;
	while (i < da->pnum)
	{
		j = 0;
		while (tab[i][j] != NULL)
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_struct(t_data *da)
{
	if (da->freed == 1)
		return ;
	del_tmpfiles(da, 0);
	if (da->args != NULL)
		free_double_tab(da->args, da);
	if (da->args_tab != NULL)
		free_double_tab(da->args_tab, da);
	if (da->in_tab != NULL)
		free_double_tab(da->in_tab, da);
	if (da->out_tab != NULL)
		free_double_tab(da->out_tab, da);
	if (da->append_tab != NULL)
		free_double_tab(da->append_tab, da);
	if (da->delim_tab != NULL)
		free_double_tab(da->delim_tab, da);
	if (da->pnum > 0 && da->exit_status != 130)
		free_pipe(da);
	if (da->my_path != NULL)
		free_tab(da->my_path);
	if (da->cmd1 != NULL)
		free_tab(da->cmd1);
	if (da->children != NULL)
		free(da->children);
	da->freed = 1;
}

void	exit_child(t_data *da)
{
	int	i;

	i = 0;
	while (da->my_env[i] != NULL)
	{
		free(da->my_env[i]);
		i++;
	}
	free(da->my_env);
	free_pipe(da);
	free_struct(da);
	exit(EXIT_FAILURE);
}

void	free_cmd_notfound(t_data *da)
{
	if (da->args != NULL)
		free_double_tab(da->args, da);
	if (da->args_tab != NULL)
		free_double_tab(da->args_tab, da);
	if (da->in_tab != NULL)
		free_double_tab(da->in_tab, da);
	if (da->out_tab != NULL)
		free_double_tab(da->out_tab, da);
	if (da->append_tab != NULL)
		free_double_tab(da->append_tab, da);
	if (da->delim_tab != NULL)
		free_double_tab(da->delim_tab, da);
	if (da->pnum > 0 && da->exit_status != 130)
		free_pipe(da);
	if (da->children != NULL)
		free(da->children);
}
