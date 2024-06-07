/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:49 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/07 14:31:33 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_env(t_data *da, char *s)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	l = 0;
	while (da->my_env[i] != NULL)
	{
		if (ft_strncmp(da->my_env[i], s, ft_strlen(s)) != 0)
		{
			while (da->my_env[i][j] != '=')
				j++;
			j++;
			while (da->my_env[i][j])
			{
				j++;
				l++;
			}
			if (l != 0)
				return (l);
		}
		i++;
	}
	return (0);
}

int	len_before_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=' && s[i])
		i++;
	return (i);
}

int	if_find_len(t_data *da, int i)
{
	int	l;
	int	j;

	l = 0;
	j = 0;
	while (da->my_env[i][j] != '=')
	{
		if (da->my_env[i][j] == '\0')
			return (0);
		j++;
	}
	j++;
	while (da->my_env[i][j])
	{
		j++;
		l++;
	}
	return (l);
}

char	*if_find(t_data *da, int i, char *res)
{
	int	l;
	int	j;

	l = 0;
	j = 0;
	while (da->my_env[i][j] != '=')
	{
		if (da->my_env[i][j] == '\0')
			return ("\n");
		j++;
	}
	j++;
	while (da->my_env[i][j])
	{
		res[l] = da->my_env[i][j];
		j++;
		l++;
	}
	if (res)
	{
		res[l] = '\0';
		return (res);
	}
	return (NULL);
}

char	*find_in_env(t_data *da, char *s)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = len_in_env(da, s);
	if (len == 0)
	{
		res = malloc(1 * sizeof(char));
		res[0] = '\0';
		return (res);
	}
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (da->my_env[i] != NULL)
	{
		if (ft_strncmp(da->my_env[i], s, len_before_equal(da->my_env[i])) == 0)
			return (if_find(da, i, res));
		i++;
	}
	res[0] = '\0';
	return (res);
}
