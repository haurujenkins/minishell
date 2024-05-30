/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:05:12 by abolea            #+#    #+#             */
/*   Updated: 2024/05/30 15:23:21 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (!res)
		return (NULL);
	return (cpy_after_digit(s, res));
}

char	*recup_after_dollar(char *s, char *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '$')
		i++;
	if (ft_isalnum(s[i + 1]) != 1 && s[i + 1] != '?' \
	&& s[i + 1] != 34 && s[i + 1] != 39)
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
	return (recup_after_dollar(s, tmp));
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
	if (!res)
		return (NULL);
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
	free (s);
	return (res);
}
