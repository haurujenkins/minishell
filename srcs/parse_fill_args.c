/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:37:45 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/20 16:00:37 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pos_cmd(char **words)
{
	int	j;

	j = 1;
	if (words[0] && (words[0][0] != '<' && words[0][0] != '>'))
		return (0);
	while (words[j])
	{
		if ((words[j - 1][0] != '<' && words[j - 1][0] != '>') && \
		(words[j][0] != '>' && words[j][0] != '<'))
			return (j);
		j++;
	}
	return (-1);
}

int	len_cmd(char *words)
{
	int		i;

	i = 0;
	while ((words[i] != '>' && words[i] != '<') && words[i])
		i++;
	return (i);
}

char	*get_cmd(char *words)
{
	char	*args;
	int		i;
	int		len;

	i = 0;
	len = len_cmd(words);
	args = malloc((len + 1) * sizeof(char));
	if (!args)
		return (NULL);
	while ((words[i] != '>' && words[i] != '<') && words[i])
	{
		args[i] = words[i];
		i++;
	}
	args[i] = '\0';
	return (args);
}

char	*fill_cmd(char **words)
{
	char	*args;
	int		i;

	i = pos_cmd(words);
	if (i == -1)
		args = NULL;
	else
		args = get_cmd(words[i]);
	if (args)
		args = cpy_args_without_quotes(args);
	return (args);
}

int	pos_args(t_data *da, char **words)
{
	int	j;

	j = da->pos_cmd + 1;
	if (j == 0)
		return (-1);
	while (words[j])
	{
		if ((words[j - 1][0] != '<' && words[j - 1][0] != '>') \
		&& (words[j][0] != '>' && words[j][0] != '<'))
			return (j);
		j++;
	}
	return (-1);
}

int	d_quotes_dollar(char *s)
{
	int		i;
	int		j;
	int		d_quotes;

	i = 0;
	j = 0;
	d_quotes = 0;
	while (s[i])
	{
		if (s[i] == 34 && s[i + 1] == '$')
		{
			i++;
			d_quotes++;
		}
		j++;
		i++;
		if (s[i] == 34 && d_quotes > 0 && d_quotes % 2 != 0)
		{
			i++;
			d_quotes++;
		}
	}
	return (j);
}

char *sup_d_quotes_before_dollar(char *s)
{
	int		i;
	int		j;
	int		d_quotes;
	char	*res;

	i = 0;
	j = 0;
	d_quotes = 0;
	res = malloc((d_quotes_dollar(s) + 1) * sizeof(char));
	while (s[i])
	{
		if (s[i] == 34 && s[i + 1] == '$')
		{
			i++;
			d_quotes++;
		}
		res[j] = s[i];
		j++;
		i++;
		if (s[i] == 34 && d_quotes > 0 && d_quotes % 2 != 0)
		{
			i++;
			d_quotes++;
		}
	}
	res[j] = '\0';
	return (res);
}

int	len_without_dollar_before_quotes(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(s[i])
	{
		if (s[i] == '$' && s[i + 1] == 34)
			i++;
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*sup_dollar_before_quotes(char *s)
{
	char	*res;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = len_without_dollar_before_quotes(s);
	res = malloc((len + 1) * sizeof(char));
	while(s[i])
	{
		if (s[i] == '$' && s[i + 1] == 34)
			i++;
		else
		{
			res[j] = s[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	return (res);
}

char	**new_temp_args(t_data *da, char **temp_args)
{
	int	i;

	i = 0;
	while (i < da->pnum)
	{
		da->nb_d = nb_dollars(temp_args[i]);
		temp_args[i] = sup_d_quotes_before_dollar(temp_args[i]);
		temp_args[i] = dollar_negative_in_s_quote(temp_args[i]);
		while (da->nb_d > 0)
		{		
			temp_args[i] = temp_without_dollar(da, temp_args[i]);
			da->nb_d--;
		}
		temp_args[i] = all_positive(temp_args[i]);
		temp_args[i] = sup_dollar_before_quotes(temp_args[i]);
		if (temp_args[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 21);
			return (NULL);
		}
		temp_args[i] = sup_delim(temp_args[i]);
		if (temp_args[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 21);
			return (NULL);
		}
		temp_args[i] = sup_append(temp_args[i]);
		if (temp_args[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 21);
			return (NULL);
		}
		i++;
	}
	return (temp_args);
}

int ft_nb_args(t_data *da, char **words)
{
	int res;
	int j;

	res = 0;
	j = pos_args(da, words);
	if (j == -1)
		return (0);
	while (words[j])
	{
		if (j > 2)
		{
			if ((words[j - 2][0] == '<' || words[j - 2][0] == '>') && (words[j][0] != '<' && words[j][0] != '>'))
			{
				if (words[j - 1][0] == 34 || words[j - 1][0] == 39)
				{
					while (if_finish_quotes(words[j - 1]) != 1)
						j++;
				}
				while (words[j] && (words[j][0] != '<' && words[j][0] != '>'))
				{
					j++;
					res++;
				}
			}
			else if ((words[j][0] == '<' || words[j][0] == '>') || (words[j - 1][0] == '<' || words[j - 1][0] == '>'))
				j++;
			else if ((words[j][0] != '<' && words[j][0] != '>') && (words[j - 1][0] != '<' && words[j - 1][0] != '>'))
			{
				j++;
				res++;
			}
		}
		else
		{
			if ((words[j][0] == '<' || words[j][0] == '>') || (words[j - 1][0] == '<' || words[j - 1][0] == '>'))
				j++;
			else if ((words[j][0] != '<' && words[j][0] != '>') && (words[j - 1][0] != '<' && words[j - 1][0] != '>'))
			{
				if (words[j][0] == 34 || words[j][0] == 39)
				{
					res++;
					j++;
				}
				else
				{
					if (if_quotes(words[j], 0) == 1)
					{
						while ((words[j] && (words[j][0] != '<' && words[j][0] != '>')))
							j++;
						res++;
					}
					else
					{
						j++;
						res++;
					}
				}
			}
		}
	}
	return (res);
}


char	*fill_args(t_data *da, char **words, int i)
{
	char	*args;

	if (da->nb_args == 0)
		return (NULL);
	else
	{
		args = ft_strdup("");
		while (words[da->i_args])
		{
			if (da->i_args > 2)
			{
				if ((words[da->i_args - 2][0] == '<' || words[da->i_args - 2][0] == '>') && (words[da->i_args][0] != '<' && words[da->i_args][0] != '>'))
				{
					if (words[da->i_args - 1][0] == 34 || words[da->i_args - 1][0] == 39)
					{
						while (if_finish_quotes(words[da->i_args  - 1]) != 1)
							da->i_args++;
					}
					while (words[da->i_args][0] != '<' && words[da->i_args ][0] != '>')
					{
						args = ft_strjoin_ori(args, words[da->i_args]);
						args = cpy_args_without_quotes(args);
						da->i_args++;
						return (args);
					}
				}
				else if ((words[da->i_args][0] == '<' || words[da->i_args][0] == '>') || (words[da->i_args - 1][0] == '<' || words[da->i_args - 1][0] == '>'))
					da->i_args++;
				else if ((words[da->i_args][0] != '<' && words[da->i_args][0] != '>') && (words[da->i_args - 1][0] != '<' && words[da->i_args - 1][0] != '>'))
				{
					args = ft_strjoin_ori(args, words[da->i_args]);
					args = cpy_args_without_quotes(args);
					da->i_args++;
					return (args);
				}
			}
			else
			{
				if ((words[da->i_args][0] == '<' || words[da->i_args][0] == '>') || (words[da->i_args - 1][0] == '<' || words[da->i_args - 1][0] == '>'))
					da->i_args++;
				else if ((words[da->i_args][0] != '<' && words[da->i_args][0] != '>') && (words[da->i_args - 1][0] != '<' && words[da->i_args - 1][0] != '>'))
				{
						args = ft_strjoin_ori(args, words[da->i_args]);
						args = cpy_args_without_quotes(args);
						da->i_args++;
						return (args);
				}
				else
				{
					if (if_quotes(words[da->i_args], 0) == 1)
					{
						while ((words[da->i_args] && (words[da->i_args][0] != '<' && words[da->i_args][0] != '>')))
						{	
							args = ft_strjoin_ori(args, words[da->i_args]);
							if (words[da->i_args + 1] && (words[da->i_args + 1][0] != '<' && words[da->i_args + 1][0] != '>'))
								args = ft_strjoin_ori(args, " ");
							da->i_args++;
						}
						if (ft_strncmp(da->args[i][0], "export", 6) != 0)
							args = cpy_args_without_quotes(args);
						da->i_args++;
						return (args);
					}
					else
					{
						args = ft_strjoin_ori(args, words[da->i_args]);
						args = cpy_args_without_quotes(args);
						da->i_args++;
						return (args);
					}
				}
			}
		}
	}
	return (NULL);
}

void	fill_args_tab(t_data *da, char **words, int i)
{
	int	j;

	j = 0;
	da->i_args = pos_args(da, words);
	da->nb_args = ft_nb_args(da, words);
	da->args_tab[i] = malloc((da->nb_args + 1) * sizeof(char *));
	if (da->nb_args == 0)
		da->args_tab[i][j] = NULL;
	else
	{
		while (j < da->nb_args)
		{
			da->args_tab[i][j] = fill_args(da, words, i);
			if (da->args_tab[i][j])
				j++;
		}
		da->args_tab[i][j] = NULL;
	}
}
