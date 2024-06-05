/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:10:19 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/05 17:17:29 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

char	**ft_realloc(char **tab, int size)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = malloc(size + 1);
	while (tab[i] != NULL)
	{
		new_tab[i] = malloc(sizeof(char) * (ft_strlen(tab[i]) + 1));
		ft_strlcpy(new_tab[i], tab[i], ft_strlen(tab[i]) + 1);
		free(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	free(tab);
	return (new_tab);
}

void	set_all(t_data *da, char **envp, int i)
{
	da->args = NULL;
	da->cmd1 = NULL;
	da->cmd = NULL;
	da->fd_input = -1;
	da->fd_output = -1;
	da->i = 0;
	da->j = 0;
	da->my_path = NULL;
	da->pid1 = 0;
	da->pid2 = 0;
	da->point_path = NULL;
	da->exit_status = 0;
	da->pnum = 0;
	da->p_in = 0;
	da->children = 0;
	da->my_env = malloc(sizeof(char *) * (ft_tablen(envp) + 1));
	while (envp[i] != NULL)
	{
		da->my_env[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		ft_strlcpy(da->my_env[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	da->my_env[i] = NULL;
}

void	exit_child(t_data *da, int index)
{
	int	i;

	i = 0;
	while (da->my_env[i] != NULL)
	{
		free(da->my_env[i]);
		i++;
	}
	rl_clear_history();
	free(da->my_env);
	free_pipe(da);
	if (da->args[index][0] != NULL)
		free_cmd(da);
	free_struct(da);
	if (da->exit_status > 0)
		exit(da->exit_status);
	exit(EXIT_FAILURE);
}

void	free_cmd_exit(t_data *da)
{
	if (da->pnum > 0 && da->exit_status != 130)
		free_pipe(da);
	if (da->children != NULL)
		free(da->children);
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
}
