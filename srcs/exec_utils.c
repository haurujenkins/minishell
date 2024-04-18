/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:10:19 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/18 15:07:58 by lle-pier         ###   ########.fr       */
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
		i++;
	}
	new_tab[i] = NULL;
	i = 0;
	while (i < ft_tablen(tab) - 1)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (new_tab);
}

void	set_all(t_data *da, char **envp)
{
	int	i;

	i = 0;
	da->cmd1 = NULL;
	da->cmd = NULL;
	da->fd_input = -1;
	da->fd_output = -1;
	da->i = 0;
	da->j = 0;
	da->my_path = NULL;
	da->pid1 = 0;
	da->point_path = NULL;
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

void free_struct(t_data *da)
{
	int i;
	int j;

	i = 0;
	if (da->args != NULL)
	{
		while (i < da->pnum)
		{
			j = 0;
			while (da->args[i][j])
			{
				free(da->args[i][j]);
				j++;
			}
			free(da->args[i]);
			i++;
		}
		free(da->args);
	}
	if (da->in_tab != NULL)
	{
		i = 0;
		while (i < da->pnum)
		{
			j = 0;
			while (da->in_tab[i][j])
			{
				free(da->in_tab[i][j]);
				j++;
			}
			free(da->in_tab[i]);
			i++;
		}
		free(da->in_tab);
	}
	if (da->out_tab != NULL)
	{
		i = 0;
		while (i < da->pnum)
		{
			j = 0;
			while (da->out_tab[i][j])
			{
				free(da->out_tab[i][j]);
				j++;
			}
			free(da->out_tab[i]);
			i++;
		}
		free(da->out_tab);
	}
	if (da->cmd1 != NULL)
	{
		i = 0;
		while (da->cmd1[i])
		{
			free(da->cmd1[i]);
			i++;
		}
		free(da->cmd1);
	}
	if (da->cmd != NULL)
		free(da->cmd);
	if (da->delim_tab != NULL)
	{
		i = 0;
		while (i < da->pnum)
		{
			j = 0;
			while (da->delim_tab[i][j])
			{
				free(da->delim_tab[i][j]);
				j++;
			}
			free(da->delim_tab[i]);
			i++;
		}
		free(da->delim_tab);
	}
	if (da->append_tab != NULL)
	{
		i = 0;
		while (i < da->pnum)
		{
			j = 0;
			while (da->append_tab[i][j])
			{
				free(da->append_tab[i][j]);
				j++;
			}
			free(da->append_tab[i]);
			i++;
		}
		free(da->append_tab);
	}
	if (da->my_path != NULL)
	{
		i = 0;
		while (da->my_path[i])
		{
			free(da->my_path[i]);
			i++;
		}
		free(da->my_path);
	}
	if (da->pipefd != NULL)
	{
		i = 0;
		while (i < da->pnum)
		{
			free(da->pipefd[i]);
			i++;
		}
		free(da->pipefd);
	}
}
