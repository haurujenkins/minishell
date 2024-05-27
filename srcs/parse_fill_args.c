/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:37:45 by lle-pier          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/27 16:29:45 by abolea           ###   ########.fr       */
=======
/*   Updated: 2024/05/24 16:42:17 by lle-pier         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	s_quotes_dollar(char *s)
{
	int		i;
	int		j;
	int		s_quotes;

	i = 0;
	j = 0;
	s_quotes = 0;
	while (s[i])
	{
		if (s[i] == 39 && s[i + 1] == 39 && s[i + 2] == '$')
		{
			i += 2;
			s_quotes += 2;
		}
		j++;
		i++;
	}
	return (j);
}

char *sup_s_quotes_before_dollar(char *s)
{
	int		i;
	int		j;
	int		s_quotes;
	char	*res;

	i = 0;
	j = 0;
	s_quotes = 0;
	res = malloc((s_quotes_dollar(s) + 1) * sizeof(char));
	while (s[i])
	{
		if (s[i] == 39 && s[i + 1] == 39 && s[i + 2] == '$')
		{
			i += 2;
			s_quotes += 2;
		}
		res[j] = s[i];
		j++;
		i++;
	}
	res[j] = '\0';
	free (s);
	return (res);
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
	free(s);
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
		if (i > 1 && (int)ft_strlen(s) > i)
		{
			if (s[i - 1] > 0 && s[i] < 0 && (s[i + 1] == 34 || s[i + 1] == 39))
				i++;
			else
			{
				i++;
				j++;
			}
		}
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
		if (i > 1 && (int)ft_strlen(s) > i)
		{
			if (s[i - 1] > 0 && s[i] < 0 && (s[i + 1] == 34 || s[i + 1] == 39))
				i++;
			else
			{
				res[j] = s[i];
				i++;
				j++;
			}
		}
		else
		{
			res[j] = s[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
<<<<<<< HEAD
	free (s);
=======
	free(s);
>>>>>>> main
	return (res);
}

char	*dollar_after_heredoc(char *s, t_data *da)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	while (i > 1)
	{
		if (s[i] == '$')
		{			
			j = i;
			while (j > 1 && !(s[j - 1] == '<' && s[j - 2] == '<'))
				j--;
			if (s[j - 1] == '<' && s[j - 2] == '<')
			{
				da->if_heredoc = 1;
				s[i] *= -1;
 				break ;
			}
		}
		i--;
	}
    return (s);
}

void	heredoc_double_quotes(char *s, t_data *da)
{
	int	i;
	
	i = 1;
	da->q_heredoc = 1;
	while (s[i])
	{
		if (s[i] < 0)
		{
			if (s[i - 1] == 34 || s[i - 1] == 39)
				da->q_heredoc = -1;
		}
		i++;
	}
}

char	*add_s_quote(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	while (ft_isalnum(s[i]) != 1)
		i++;
	len = i;
	if (i > 1)
	{
		if (s[i - 1] != 39)
			return (s);
	}
	i = 0;
	tmp = malloc((ft_strlen(s) + 2) * sizeof(char));
	while (s[i])
	{
		if (i > len && s[i] == 34)
		{
			tmp[j] = 39;
			j++;
		}
		tmp[j] = s[i];
		j++;
		i++;
	}
	tmp[i] = '\0';
	free (s);
	return (tmp);
}

void	new_temp_args(t_data *da, char **temp_args)
{
	int	i;
	int	tmp_d;

	i = 0;
	da->if_heredoc = 0;
	while (i < da->pnum)
	{
		da->nb_d = nb_dollars(temp_args[i]);
		tmp_d = da->nb_d;
		temp_args[i] = dollar_negative_in_s_quote(temp_args[i]);
		while (tmp_d > 0)
		{
			temp_args[i] = dollar_after_heredoc(temp_args[i], da);
			tmp_d--;
		}
		heredoc_double_quotes(temp_args[i], da);
		if (da->if_heredoc == 0)
		{
			while (da->nb_d > 0)
			{
				// temp_args[i] = sup_d_quotes_before_dollar(temp_args[i]);
				temp_args[i] = sup_s_quotes_before_dollar(temp_args[i]);
				temp_args[i] = temp_without_dollar(da, temp_args[i]);
				temp_args[i] = add_s_quote(temp_args[i]);
				da->nb_d--;
			}
		}
		if (nb_dollars(temp_args[i]) != 0)
		{
			temp_args[i] = sup_d_quotes_before_dollar(temp_args[i]);
			temp_args[i] = sup_dollar_before_quotes(temp_args[i]);
		}
		if (temp_args[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 21);
			return ;
		}
		temp_args[i] = sup_delim(temp_args[i]);
		if (temp_args[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 21);
			return ;
		}
		temp_args[i] = sup_append(temp_args[i]);
		if (temp_args[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 21);
			return ;
		}
		i++;
	}
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
					j++;
					res++;
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
