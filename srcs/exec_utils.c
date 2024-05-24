/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:10:19 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/23 11:40:40 by lle-pier         ###   ########.fr       */
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

void	free_args(int i, int pnum, t_data *da)
{
	int	d;
	int	k;
	int	l;
	int	m;
	int	n;

	i = 0;
	while (i < pnum)
	{
		//write(1, "free_args\n", 10);
		d = 0;
		while (da->args_tab[i][d])
		{
			//write(1, "args_tab\n", 9);
			free(da->args_tab[i][d]);
			d++;
		}
		free(da->args_tab[i]);
		k = 0;
		while (da->in_tab[i][k])
		{
			//write(1, "in_tab\n", 7);
			free(da->in_tab[i][k]);
			k++;
		}
		free(da->in_tab[i]);
		l = 0;
		while (da->out_tab[i][l])
		{
			//write(1, "out_tab\n", 8);
			free(da->out_tab[i][l]);
			l++;
		}
		free(da->out_tab[i]);
		m = 0;
		while (da->delim_tab[i][m])
		{
			//write(1, "delim_tab\n", 10);
			free(da->delim_tab[i][m]);
			m++;
		}
		free(da->delim_tab[i]);
		n = 0;
		while (da->append_tab[i][n])
		{
			//write(1, "append_tab\n", 11);
			free(da->append_tab[i][n]);
			n++;
		}
		free(da->append_tab[i]);
		i++;
	}
}

void	free_struct(t_data *da)
{
	del_tmpfiles(da, 0);
	free_args(0, da->pnum, da);
}
