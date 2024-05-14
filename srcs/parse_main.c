/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/05/14 10:52:17 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(char *rl)
{
	int	i;

	i = 0;
	if (rl[i] == '|')
		return (-1);
	while (rl[i])
	{
		if (rl[i] == 34)
		{
			i++;
			while (rl[i] != 34 && rl[i])
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

char	*negative_in_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			i++;
			while (s[i] && s[i] != 34)
			{
				if (s[i] == ' ' || s[i] == '|')
					s[i] *= -1;
				i++;
			}
		}
		else if (s[i] == 39)
		{
			i++;
			while (s[i] && s[i] != 39)
			{
				if (s[i] == ' ' || s[i] == '|')
					s[i] *= -1;
				i++;
			}
		}
		i++;
	}
	return (s);
}

char	*all_positive(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < 0)
			s[i] *= -1;
		i++;
	}
	return (s);
}

int	parsing(char *rl, t_data *da)
{
	char	**temp_args;
	char	**words;
	int		i;
	int		j;
	int		num_w;	

	i = 0;
	temp_args = NULL;
	words = NULL;
	da->pnum = nb_pipe(rl);
	num_w = 0;
	rl = negative_in_quotes(rl);
	temp_args = ft_split(rl, '|');
	if (temp_args == NULL)
		return (printf ("Error: malloc failed\n"), 1);
	while (temp_args[i])
	{
		temp_args[i] = all_positive(temp_args[i]);
		i++;
	}
	i = 0;
	da->args = malloc(da->pnum * sizeof(char **));
	if (da->args == NULL)
		return (printf("Error: malloc failed\n"), 1);
	if (fill_delim_tab(da, temp_args) == 1)
		return (1);
	if (fill_append_tab(da, temp_args) == 1)
		return (1);
	temp_args = new_temp_args(da, temp_args);
	if (temp_args == NULL)
		return (1);
	da->args_tab = malloc(da->pnum * sizeof(char **));
	if (!da->args_tab)
		return (1);
	da->in_tab = malloc(da->pnum * sizeof(char **));
	if (!da->in_tab)
		return (1);
	da->out_tab = malloc(da->pnum * sizeof(char **));
	if (!da->out_tab)
		return (1);
	while (i < da->pnum)
	{
		if_quotes_not_close(temp_args, i);
		temp_args[i] = new_temp(temp_args[i]);
		temp_args[i] = negative_in_quotes(temp_args[i]);
		words = ft_split(temp_args[i], ' ');
		j = 0;
		while (words[j])
		{
			words[j] = all_positive(words[j]);
			j++;
		}
		temp_args[i] = all_positive(temp_args[i]);
		while (words[num_w] != NULL)
			num_w++;
		da->args[i] = malloc((num_w + 1) * sizeof(char *));
		if (da->args[i] == NULL)
			return (printf("Error: malloc failed\n"), 1);
		da->args[i][0] = fill_cmd(words);
		da->args[i][1] = NULL;
		da->pos_cmd = pos_cmd(words);
		da->io_nb = 0;
		fill_args_tab(da, words, i);
		fill_intab(da, temp_args[i], i);
		fill_outab(da, temp_args[i], i);
		i++;
	}
	i = -1;
	while (temp_args[++i] != NULL)
		free(temp_args[i]);
	free(temp_args);
	num_w = -1;
	while (words[++num_w] != NULL)
		free(words[num_w]);
	free(words);
	words = NULL;
	print_args(i, da->pnum, da);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_data	da;

	(void)envp;
	if (argc != 1 || argv[0][0] == '\0')
		printf("ERROR\n");
	set_all(&da, envp);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		rl = readline("\033[1;36m<3 \033[0;37m");
		if (!rl)
		{
			free_struct(&da);
			break ;
		}
		if (check_error(rl))
		{
			write(2, "parse error\n", 12);
			continue ;
		}
		if (rl[0])
		{
			if (parsing(rl, &da) == 1)
			{
				add_history(rl);
				free(rl);
				free_struct(&da);
			}
			else
			{
				heredoc_replace(&da, 0);
				signal(SIGINT, sigint_handler);
				print_args(0, da.pnum, &da);
				add_history(rl);
				free(rl);
				if (da.args[0][0])
					main_exec(&da, envp);
				free_struct(&da);
			}
		}
	}
	return (0);
}
