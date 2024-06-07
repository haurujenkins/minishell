/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:33 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/07 14:39:07 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_path(t_data *da, char **envp)
{
	da->i = 0;
	while (!(da->my_env[da->i++] == NULL))
	{
		if (ft_strchr(da->my_env[da->i], "PATH="))
		{
			da->point_path = envp[da->i] + 5;
			da->my_path = ft_split(da->point_path, ':');
			if (da->my_path == NULL)
				return (free_data(da, envp), 1);
			return (0);
		}
	}
	da->my_path = malloc(sizeof(char *) * 2);
	if (da->my_path == NULL)
	{
		free_data(da, envp);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	da->my_path[0] = ft_strdup("null\0");
	da->my_path[1] = NULL;
	return (0);
}

char	*get_home(char **envp)
{
	char	*home;
	int		i;

	home = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			home = ft_strdup(envp[i] + 5);
			break ;
		}
		i++;
	}
	return (home);
}

void	alloc_cmd1(t_data *da, char **envp, int index)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 1;
	len = ft_tablen(da->args_tab[index]);
	da->cmd1 = malloc(sizeof(char *) * (len + 2));
	if (da->cmd1 == NULL)
	{
		free_data(da, envp);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	da->cmd1[0] = ft_strdup(da->args[index][0]);
	while (da->args_tab[index][++i] != NULL)
	{
		da->cmd1[j] = ft_strdup(da->args_tab[index][i]);
		j++;
	}
	da->cmd1[j] = NULL;
}

int	get_args_builtins(t_data *da, int index, char **envp)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	if (da->args_tab[0] == NULL)
	{
		da->cmd1 = malloc(sizeof(char *) * 2);
		da->cmd1[0] = ft_strdup(da->args[index][0]);
		da->cmd1[1] = NULL;
	}
	else
	{
		alloc_cmd1(da, envp, index);
	}
	return (0);
}

void	get_args(t_data *da, char **envp, int index)
{
	if (da->args_tab[index][0] == NULL)
	{
		da->cmd1 = malloc(sizeof(char *) * 2);
		if (da->cmd1 == NULL)
		{
			free_data(da, envp);
			perror("malloc");
			exit_child(da, index);
		}
		da->cmd1[0] = ft_strdup(da->args[index][0]);
		da->cmd1[1] = NULL;
	}
	else
		alloc_cmd1(da, envp, index);
	get_path(da, envp);
}
