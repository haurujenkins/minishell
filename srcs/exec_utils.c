/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:10:19 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/06 15:22:16 by lle-pier         ###   ########.fr       */
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

void	set_all(t_data *da, char **envp)
{
	int	i;

	i = 0;
	da->args = NULL;
	da->cmd1 = NULL;
	da->cmd = NULL;
	da->fd_input = -1;
	da->fd_output = -1;
	da->i = 0;
	da->j = 0;
	da->my_path = NULL;
	da->pid1 = 0;
	da->point_path = NULL;
	da->exit_status = 0;
	da->pnum = 0;
	da->p_in = 0;
	da->my_env = malloc(sizeof(char *) * (ft_tablen(envp) + 1));
	while (envp[i] != NULL)
	{
		da->my_env[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		ft_strlcpy(da->my_env[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	da->my_env[i] = NULL;
}

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
}

void	free_tab(char **tab, t_data *da)
{
	int	i;

	i = 0;
	while (i < da->pnum)
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
	return ;
	if (da->args != NULL)
		free_double_tab(da->args, da);
	if (da->in_tab != NULL)
		free_double_tab(da->in_tab, da);
	if (da->out_tab != NULL)
		free_double_tab(da->out_tab, da);
	if (da->cmd1 != NULL)
		free_tab(da->cmd1, da);
	if (da->cmd != NULL)
	{
		free(da->cmd);
		da->cmd = NULL;
	}
	if (da->delim_tab != NULL)
		free_double_tab(da->delim_tab, da);
	if (da->append_tab != NULL)
		free_double_tab(da->append_tab, da);
	if (da->my_path != NULL)
		free_tab(da->my_path, da);
	if (da->pipefd != NULL)
		free_pipe(da);
}
