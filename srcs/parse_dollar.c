/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:22 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/24 16:24:33 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nb_dollars(char *s)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (s[i])
	{
		if (s[i] == '$' && (ft_isalnum(s[i + 1]) == 1 || s[i + 1] == '?' || s[i + 1] == 39 || s[i + 1] == 34))
			d++;
		i++;
	}
	return (d);
}

int	len_after_dollar(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '$')
		i++;
	if (i > 1)
	{
		if (s[i - 1] != 39)
			j++;
	}
	i++;
	while (ft_isalnum(s[i]) == 1 || s[i] == '?')
	{
		i++;
		j++;
	}
	return (j);
}

int	nb_after_dollar(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[0]) == 1)
		return (1);
	while (s[i])
	{
		if (s[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

int	len_after_digit(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_isdigit(s[0]) == 1)
	{
		i++;
		while (s[i])
		{
			j++;
			i++;
		}
		return (j);	
	}
	while (s[i] != 39)
		i++;
	i++;
	while (s[i])
	{
		j++;
		i++;
	}
	return (j);
}

char	*recup_after_digit(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	len = len_after_digit(s);
	res = malloc((len + 1) * sizeof(char));
	if (ft_isdigit(s[0]) == 1)
	{
		i++;
		while (s[i])
		{
			res[j] = s[i];
			j++;
			i++;
		}
		res[j] = '\0';
		return (res);	
	}
	while (s[i] != 39)
		i++;
	while (s[i] == 39)
		i++;
	while (s[i])
	{
		res[j] = s[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*after_dollar(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	if (if_dollar(s) == 0)
		return (NULL);
	len = len_after_dollar(s) + 1;
	tmp = malloc(len * sizeof(char));
	if (tmp == NULL)
		return (write(2, "Malloc failed\n", 14), NULL);
	while (s[i] != '$')
		i++;
	if (ft_isalnum(s[i + 1]) != 1 && s[i + 1] != '?' && s[i + 1] != 34 && s[i + 1] != 39)
		return (NULL);
	i++;
	while (ft_isalnum(s[i]) == 1 || s[i] == '?')
	{
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*s_quotes_new_args_negative(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 39)
			s[i] *= -1;
		i++;
	}
	return (s);
}

char	*add_d_quotes_newargs(char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(((int)ft_strlen(s) + 3) * sizeof(char));
	while (s[i])
	{
		if (i == 0)
		{
			res[j] = 34;
			j++;
		}
		res[j] = s[i];
		j++;
		i++;
	}
	res[j] = 34;
	j++;
	res[j] = '\0';
	return (res);
}

char	*temp_without_dollar(t_data *da, char *temp_args)
{
	int		i;
	int		j;
	int		k;
	int		s_quote;
	int		len;
	char	*new_args;
	char	*before_args;
	char	*res;

	i = 0;
	j = 0;
	k = 0;
	s_quote = 0;
	before_args = after_dollar(temp_args);
	if (before_args == NULL)
	{
		return (temp_args);
	}
	// if (before_args[0] == '$')
	// 	s_quote = 2;
	if (s_quote != 0)
		return (cpy_args_without_s_quotes(temp_args));
	if (nb_after_dollar(before_args) == 1)
		new_args = recup_after_digit(before_args);
	else if (before_args[0] == '?')
		new_args = ft_itoa(da->exit_status);
	else
		new_args = find_in_env(da, before_args);
	if (new_args[0] == 39)
		new_args = add_d_quotes_newargs(new_args);
	len = (ft_strlen(temp_args) - da->nb_d + ft_strlen(new_args) + s_quote + 1);
	res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
	{
		write(2, "Malloc failed\n", 14);
		free(before_args);
		free(temp_args);
		free(new_args);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (temp_args[i] != '$')
	{
		res[j] = temp_args[i];
		i++;
		j++;
	}
	while (new_args[k])
	{
		res[j] = new_args[k];
		j++;
		k++;
	}
	i++;
	if (temp_args[i] == '?')
	{
		i++;
		while (temp_args[i])
		{
			res[j] = temp_args[i];
			i++;
			j++;
		}
	}
	while (temp_args[i] != ' ' && temp_args[i] != '$' && (ft_isalnum(temp_args[i]) == 1 || temp_args[i] == 39) && temp_args[i])
		i++;
	while (temp_args[i])
	{
		res[j] = temp_args[i];
		i++;
		j++;
	}
	res[j] = '\0';
	free(before_args);
	free(temp_args);
	free(new_args);
	return (res);
}
