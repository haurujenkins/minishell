/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/04/12 16:46:59 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(char *rl)
{
	int	i;

	i = 0;
	while (rl[i])
	{
		if (rl[i] == 34)
		{
			i++;
			while (rl[i] != 34)
				i++;
		}
		if (rl[i] == '<' && rl[i + 1] == '>')
			return (-1);
		else if (rl[i] == '>' && rl[i + 1] == '<')
			return (-1);
		i++;
	}
	return (0);
}

int	simple_quote_close(char *temp_args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (temp_args[i])
	{
		if (temp_args[i] == 39)
		{
			i++;
			k++;
			while (temp_args[i])
			{
				if (temp_args[i] == 39)
					j++;
				i++;
			}
		}
		i++;
	}
	if (j == 0 && k != 0)
		return (0);
	return (1);
}

int	double_quotes_close(char *temp_args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (temp_args[i])
	{
		if (temp_args[i] == 34)
		{
			i++;
			k++;
			while (temp_args[i])
			{
				if (temp_args[i] == 34)
					j++;
				i++;
			}
		}
		i++;
	}
	if (j == 0 && k != 0)
		return (0);
	return (1);
}

void	print_args(int i, int pnum, t_data *da)
{
	int	j;
	int	k;
	int	l;
	int	m;
	int	n;

	i = 0;
	while (i < pnum)
	{
		printf("\033[1;34m\nCommande %d:\033[0;37m\n\n", i + 1);
		j = 0;
		printf("\033[0;31mcmd[%d][%d]\033[0;37m = %s\n", i, j, da->args[i][0]);
		j++;
		if (da->args[i][j])
			printf("\n");
		while (da->args[i][j])
		{
			printf("\033[0;33margs[%d][%d]\033[0;37m = %s\n", i, j, da->args[i][j]);
			j++;
		}
		k = 0;
		if (da->in_tab[i][k])
			printf("\n");
		while (da->in_tab[i][k])
		{
			printf("\033[0;32minput[%d][%d]\033[0;37m = %s\n", i, k, da->in_tab[i][k]);
			k++;
		}
		l = 0;
		if (da->out_tab[i][l])
			printf("\n");
		while (da->out_tab[i][l])
		{
			printf("\033[0;35moutput[%d][%d]\033[0;37m = %s\n", i, l, da->out_tab[i][l]);
			l++;
		}
		m = 0;
		if (da->delim_tab[i][m])
			printf("\n");
		while (da->delim_tab[i][m])
		{
			printf("delimiteur[%d][%d]\033[0;37m = %s\n", i, m, da->delim_tab[i][m]);
			m++;
		}
		n = 0;
		if (da->append_tab[i][n])
			printf("\n");
		while (da->append_tab[i][n])
		{
			printf("append_out[%d][%d]\033[0;37m = %s\n", i, n, da->append_tab[i][n]);
			n++;
		}
		i++;
	}
	printf("\n");
}

int	nb_pipe(char *rl)
{
	int	pnum;
	int	i;

	i = 0;
	pnum = 1;
	while (rl[i])
	{
		if (rl[i] == '|')
			pnum++;
		i++;
	}
	return (pnum);
}

int	ft_strlen_char(char *s, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[len + i])
	{
		if (s[len + i] == c)
			break ;
		else
			len++;
	}
	return (len);
}

char	*cpy_until_char(char *s, char c, int start)
{
	char	*tmp;
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(s);
	tmp = malloc((len - start + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (s[start] != c && start < len)
	{
		tmp[j] = s[start];
		start++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	if_quotes_not_close(char **temp_args, int i)
{
	if (simple_quote_close(temp_args[i]) == 0)
		exit(printf("Error : simple quote not close\n"));
	else if (double_quotes_close(temp_args[i]) == 0)
		exit(printf("Error : double quotes not close\n"));
	else
		return ;
}

int	pos_cmd(char **words)
{
	int	j;

	j = 1;
	if ((words[0][0] != '<' && words[0][0] != '>'))
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

int	pos_args(char **words)
{
	int	j;

	j = pos_cmd(words) + 1;
	if (j == 0)
		return (-1);
	while (words[j])
	{
		if ((words[j - 1][0] !=  '<' && words[j - 1][0] != '>') && \
		(words[j][0] != '>' && words[j][0] != '<'))
			return (j);
		else if (((words[j - 1][0] == '<' && words[j - 1][0] == '>') || words[j - 1][1]) && \
		(words[j][0] != '>' && words[j][0] != '<'))
			return (j);
		j++;
	}
	return (-1);
}

char	*fill_cmd(char **words)
{
	char	*args;
	int		i;

	i = pos_cmd(words);
	if (i == -1)
		args = NULL;
	else
		args = ft_strdup(words[i]);
	return (args);
}

int	if_finish_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] == 34)
		return (1);
	return (0);
}

int	nb_quotes(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] == 34)
			res++;
		i++;
	}
	return (res);
}

char	*cpy_args_without_quotes(char *s)
{
	int		i;
	int		j;
	char	*tmp;
	
	i = 0;
	j = 0;
	tmp = malloc((ft_strlen(s) - nb_quotes(s) + 1) * sizeof(char));
	while (s[i])
	{
		while (s[i] == 34)
			i++;
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*fill_args(char **words)
{
	char	*args;
	int		j;
	int		num_words;

	num_words = 0;
	while (words[num_words])
		num_words++;
	j = pos_args(words);
	if (j == -1)
		args = NULL;
	else
	{
		args = ft_strdup("");
		while (j < num_words && words[j][0] != '<' && words[j][0] != '>')
		{
			if ((words[j - 1][0] == '>' || words[j - 1][0] == '<') && (words[j][0] == 34 || words[j - 1][1] == 34))
			{
				while (if_finish_quotes(words[j - 1]) != 1)
					j++;
			}
			else if (words[j][0] == '<' && words[j][0] == '>')
			{
				if (words[j - 1][0] == 34 || words[j - 1][1] == 34)
				{
					while (if_finish_quotes(words[j - 1]) != 1)
						j++;
				}
				else
					j++;
			}
			else
			{
				args = ft_strjoin_ori(args, words[j]);
				args = ft_strjoin_ori(args, " ");
				j++;
			}
		}
		while (j < num_words)
		{
			if ((words[j - 2][0] == '<' || words[j - 2][0] == '>') && !words[j - 2][1])
			{
				if (words[j - 1][0] == 34)
				{
					while (if_finish_quotes(words[j - 1]) != 1)
						j++;
				}
				while (j < num_words && (words[j][0] != '<' && words[j][0] != '>'))
				{
					args = ft_strjoin_ori(args, words[j]);
					args = ft_strjoin_ori(args, " ");
					j++;
				}
			}
			else if ((words[j - 1][0] == '<' || words[j - 1][0] == '>') && words[j - 1][1])
			{
				if (words[j - 1][1] == 34)
				{
					while (if_finish_quotes(words[j - 1]) != 1)
						j++;
				}
				while (j < num_words && (words[j][0] != '<' && words[j][0] != '>'))
				{
					args = ft_strjoin_ori(args, words[j]);
					args = ft_strjoin_ori(args, " ");
					j++;
				}
			}
			j++;
		}
	}
	if (args != NULL)
		args = cpy_args_without_quotes(args);
	return (args);
}

int		ft_nb_redir(char *temp_args, char c)
{
	int	i;
	int	nb;
	
	i = 0;
	nb = 0;
	while (temp_args[i])
	{
		if (temp_args[i] == 34)
		{
			i++;
			while (temp_args[i] != 34)
				i++;
		}
		if (temp_args[i] == c)
			nb++;
		i++;
	}
	return (nb);
}

int	if_quotes(char *s, int start)
{
	while (s[start] != ' ')
	{
		if (s[start] == 34)
			return (1);
		start++;
	}
	return (0);
}

int	if_io_before_last_quotes(char *s, char c, int start)
{
	while(s[start])
	{
		if (s[start] == 34)
		{
			start++;
			while (s[start] != 34)
				start++;
			if (s[start] == 34 && s[start - 1] == c)
				return (1);
		}
		start++;
	}
	return (0);
}

char	*fill_input(char *temp_args, t_data *da)
{
	char	*args;

	while (temp_args[da->io_nb])
	{
		if (temp_args[da->io_nb] == '<')
		{
			da->io_nb++;
			if (temp_args[da->io_nb] == ' ')
			{
				da->io_nb++;
				while (temp_args[da->io_nb] == ' ')
					da->io_nb++;
				if (temp_args[da->io_nb] == 34)
				{
					da->io_nb++;
					args = cpy_until_char(temp_args, 34, da->io_nb);
					while (temp_args[da->io_nb] != 34)
						da->io_nb++;
					return (args);
				}
				else
				{
					args = cpy_until_char(temp_args, ' ', da->io_nb);
					return (args);
				}
			}
			else if (temp_args[da->io_nb] == 34)
			{
				da->io_nb++;
				args = cpy_until_char(temp_args, 34, da->io_nb);
				while (temp_args[da->io_nb] != 34)
					da->io_nb++;
				return (args);
			}
			else if (ft_isprint(temp_args[da->io_nb]) == 1)
			{
				args = cpy_until_char(temp_args, ' ', da->io_nb);
				if (if_finish_quotes(args) == 1)
					return (NULL);
				return (args);
			}
		}
		da->io_nb++;
	}
	return (NULL);
}

void	fill_intab(t_data *da, char **temp_args)
{
	int	i;
	int	j;

	i = 0;
	da->nb_redir_in = 0;
	da->in_tab = malloc(da->pnum * sizeof(char **));
	while (i < da->pnum)
	{
		j = 0;
		da->io_nb = 0;
		da->nb_redir_in = ft_nb_redir(temp_args[i], '<');
		da->in_tab[i] = malloc((da->nb_redir_in + 1) * sizeof(char *));
		if (da->nb_redir_in == 0)
			da->in_tab[i][j] = NULL;
		else
		{
			while (j < da->nb_redir_in)
			{
				da->in_tab[i][j] = fill_input(temp_args[i], da);
				if (da->in_tab[i][j])
					j++;
			}
			da->in_tab[i][j] = NULL;
		}
		i++;
	}
}

char	*fill_output(char *temp_args, t_data *da)
{
	char	*args;
	
	while (temp_args[da->io_nb])
	{
		if (temp_args[da->io_nb] == '>')
		{
			da->io_nb++;
			if (temp_args[da->io_nb] == ' ')
			{
				da->io_nb++;
				while (temp_args[da->io_nb] == ' ')
					da->io_nb++;
				if (temp_args[da->io_nb] == 34)
				{
					da->io_nb++;
					args = cpy_until_char(temp_args, 34, da->io_nb);
					while (temp_args[da->io_nb] != 34)
						da->io_nb++;
					return (args);
				}
				else
				{
					args = cpy_until_char(temp_args, ' ', da->io_nb);
					return (args);
				}
			}
			else if (temp_args[da->io_nb] == 34)
			{
				da->io_nb++;
				args = cpy_until_char(temp_args, 34, da->io_nb);
				while (temp_args[da->io_nb] != 34)
					da->io_nb++;
				return (args);
			}
			else if (ft_isprint(temp_args[da->io_nb]) == 1)
			{
				args = cpy_until_char(temp_args, ' ', da->io_nb);
				if (if_finish_quotes(args) == 1)
					return (NULL);
				return (args);
			}
		}
		da->io_nb++;
	}
	return (NULL);
}

void	fill_outab(t_data *da, char **temp_args)
{
	int	i;
	int	j;

	i = 0;
	da->nb_redir_out = 0;
	da->out_tab = malloc(da->pnum * sizeof(char **));
	while (i < da->pnum)
	{
		j = 0;
		da->io_nb = 0;
		da->nb_redir_out = ft_nb_redir(temp_args[i], '>');
		da->out_tab[i] = malloc((da->nb_redir_out + 1) * sizeof(char *));
		if (da->nb_redir_out == 0)
			da->out_tab[i][j] = NULL;
		else
		{
			while (j < da->nb_redir_out)
			{
				da->out_tab[i][j] = fill_output(temp_args[i], da);
				if (da->out_tab[i][j])
					j++;
			}
			da->out_tab[i][j] = NULL;
		}
		i++;
	}
}

int	ft_nb_delim(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			i++;
			while (s[i] != 34)
				i++;
		}
		if (s[i] == '<' && s[i + 1] == '<')
			j++;
		i++;
	}
	return (j);
}

char	*fill_delimiter(char *temp_args, t_data *da)
{
	char	*args;

	while (temp_args[da->in_delim])
	{
		if (temp_args[da->in_delim] == '<' && temp_args[da->in_delim + 1] == '<')
		{
			da->in_delim += 2;
			if (temp_args[da->in_delim] == ' ')
			{
				da->in_delim++;
				while (temp_args[da->in_delim] == ' ')
					da->in_delim++;
				if (temp_args[da->in_delim] == 34)
				{
					da->in_delim++;
					args = cpy_until_char(temp_args, 34, da->in_delim);
					while (temp_args[da->in_delim] != 34)
						da->in_delim++;
					return (args);
				}
				else
				{
					args = cpy_until_char(temp_args, ' ', da->in_delim);
					return (args);
				}
			}
			else if (temp_args[da->in_delim] == 34)
			{
				da->in_delim++;
				args = cpy_until_char(temp_args, 34, da->in_delim);
				while (temp_args[da->in_delim] != 34)
					da->in_delim++;
				return (args);
			}
			else if (ft_isprint(temp_args[da->in_delim]) == 1)
			{
				args = cpy_until_char(temp_args, ' ', da->in_delim);
				if (if_finish_quotes(args) == 1)
					return (NULL);
				return (args);
			}
		}
		da->in_delim++;
	}
	return (NULL);
}

void	fill_delim_tab(t_data *da, char **temp_args)
{
	int	i;
	int	j;

	i = 0;
	da->in_delim = 0;
	da->delim_tab = malloc(da->pnum * sizeof(char **));
	while (i < da->pnum)
	{
		j = 0;
		da->nb_delim = ft_nb_delim(temp_args[i]);
		da->delim_tab[i] = malloc((da->nb_delim + 1) * sizeof(char *));
		if (da->nb_delim == 0)
			da->delim_tab[i][j] = NULL;
		else
		{
			while (j < da->nb_delim)
			{
				da->delim_tab[i][j] = fill_delimiter(temp_args[i], da);
				if (da->delim_tab[i][j])
					j++;
			}
			da->delim_tab[i][j] = NULL;
		}
		i++;
	}
}

int	len_without_delim(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
		{
			i += 3;
			while (s[i] != ' ' && s[i])
				i++;
			while (s[i] == ' ')
				i++;
		}
		else if (s[i])
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*sup_delim(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = len_without_delim(s);
	tmp = malloc((len + 1) * sizeof(char));
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
		{
			i += 3;
			while (s[i] != ' ' && s[i])
				i++;
			while (s[i] == ' ')
				i++;
		}
		else if (s[i])
		{
			tmp[j] = s[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

int	ft_nb_append(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			i++;
			while (s[i] != 34)
				i++;
		}
		if (s[i] == '>' && s[i + 1] == '>')
			j++;
		i++;
	}
	return (j);
}

char	*fill_append(char *temp_args, t_data *da)
{
	char	*args;

	while (temp_args[da->o_append])
	{
		if (temp_args[da->o_append] == '>' && temp_args[da->o_append + 1] != '>')
		{
			args = ft_strdup("0");
			da->o_append++;
			return (args);
		}
		else if (temp_args[da->o_append] == '>' && temp_args[da->o_append + 1] == '>')
		{
			args = ft_strdup("1");
			da->o_append += 2;
			return (args);
		}
		da->o_append++;
	}
	return (NULL);
}

void	fill_append_tab(t_data *da, char **temp_args)
{
	int	i;
	int	j;

	i = 0;
	da->o_append = 0;
	da->append_tab = malloc(da->pnum * sizeof(char **));
	while (i < da->pnum)
	{
		j = 0;
		da->nb_append = ft_nb_append(temp_args[i]);
		da->append_tab[i] = malloc((da->nb_append + 1) * sizeof(char *));
		if (da->nb_append == 0)
			da->append_tab[i][j] = NULL;
		else
		{
			while (j < ft_nb_redir(temp_args[i], '>') - da->nb_append)
			{
				da->append_tab[i][j] = fill_append(temp_args[i], da);
				if (da->append_tab[i][j])
					j++;
			}
			da->append_tab[i][j] = NULL;
		}
		i++;
	}
}

int	len_without_append(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '>' && s[i + 1] == '>')
			i++;
		else if (s[i])
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*sup_append(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = len_without_append(s);
	tmp = malloc((len + 1) * sizeof(char));
	while (s[i])
	{
		if (s[i] == '>' && s[i + 1] == '>')
		{
			i++;
		}
		else if (s[i])
		{
			tmp[j] = s[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

int	nb_io(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] == '<' || s[i] == '>') && (s[i + 1] == '<' || s[i + 1] == '>'))
			j++;
		i++;
	}
	return (j);
}

int	if_dollar(char *s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	len_after_dollar(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '$')
		i++;
	while (ft_isalnum(s[i]) == 1)
	{
		i++;
		j++;
	}
	return (j);
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
	len = len_after_dollar(s);
	tmp = malloc((len + 1) * sizeof(char));
	while (s[i] != '$')
		i++;
	i++;
	while (ft_isalnum(s[i]) == 1)
	{
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

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

char	*find_in_env(t_data *da, char *s)
{
	int		i;
	int		j;
	int		l;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	l = 0;
	len = len_env(da, s);
	res = malloc(sizeof(len + 1) * sizeof(char));
	while (da->my_env[i] != NULL)
	{
		if (ft_strncmp(da->my_env[i], s, ft_strlen(s)) == 0)
		{
			while (da->my_env[i][j] != '=')
				j++;
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
		}
		i++;
	}
	return (NULL);
}

char	*temp_without_dollar(t_data *da, char *temp_args)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*new_args;
	char	*before_args;
	char	*res;

	i = 0;
	j = 0;
	k = 0;
	before_args = after_dollar(temp_args);
	if (before_args == NULL)
		return (temp_args);
	new_args = find_in_env(da, before_args);
	len = (ft_strlen(temp_args) - len_after_dollar(temp_args) - 1) + len_env(da, before_args) + 2;
	printf("len = %d\n", len);
	res = malloc(len * sizeof(char));
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
	res[j] = '\0';
	return (res);
}

char	**new_temp_args(t_data *da, char **temp_args)
{
	int	i;

	i = 0;
	while (i < da->pnum)
	{
		temp_args[i] = temp_without_dollar(da, temp_args[i]);
		temp_args[i] = sup_delim(temp_args[i]);
		temp_args[i] = sup_append(temp_args[i]);
		i++;
	}
	return (temp_args);
}

void	parsing(char *rl, t_data *da)
{
	char	**temp_args;
	char	**words;
	int		i;
	int		num_words;	

	i = 0;
	da->pnum = nb_pipe(rl);
	num_words = 0;
	temp_args = ft_split(rl, '|');
	da->args = malloc(da->pnum * sizeof(char **));
	while (i < da->pnum)
	{
		if_quotes_not_close(temp_args, i);
		after_dollar(temp_args[i]);
		fill_delim_tab(da, temp_args);
		fill_append_tab(da, temp_args);
		temp_args = new_temp_args(da, temp_args);
		words = ft_split(temp_args[i], ' ');
		while (words[num_words] != NULL)
			num_words++;
		da->args[i] = malloc((num_words + 1) * sizeof(char *));
		da->args[i][0] = fill_cmd(words);
		if (num_words > 1)
		{
			da->args[i][1] = fill_args(words);
			da->args[i][2] = NULL;
		}
		else
			da->args[i][1] = NULL;
		da->io_nb = 0;
		fill_intab(da, temp_args);
		fill_outab(da, temp_args);
		i++;
	}
	print_args(i, da->pnum, da);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_data	da;
	
	
	(void)envp;
	if (argc != 1 || argv[0][0] == '\0')
		printf("ERROR\n");
	set_all(&da, envp);
	// print_all();
	while (1)
	{
		rl = readline("\033[1;36m<3 \033[0;37m");
		if (check_error(rl))
		{
			printf("parse error\n");
			continue;
		}
		if (rl[0])
		{
			parsing(rl, &da);
			// main_exec(&da, envp);
			add_history(rl);
		}
		else
			continue ;
	}
	return (0);
}
