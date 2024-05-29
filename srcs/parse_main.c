/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/05/29 11:27:19 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quote_close(char	*rl)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 1;
	s_quote = 1;
	while (rl[i])
	{
		if (rl[i] == 34 && s_quote > 0)
			d_quote *= -1;
		if (rl[i] == 39 && d_quote > 0)
			s_quote *= -1;
		i++;
	}
	if (d_quote < 0 || s_quote < 0)
		return (-1);
	else
		return (0);
}

int	check_rl(char *rl, int i)
{
	if (rl[i] == '|' && rl[i + 1] == '|')
		return (-1);
	if (rl[i] == '<' && rl[i + 1] == '>')
		return (-1);
	else if (rl[i] == '>' && rl[i + 1] == '<')
		return (-1);
	else if (rl[i] == '<' && rl[i + 1] == '<' && rl[i + 2] == '<')
		return (-1);
	else if (rl[i] == '>' && rl[i + 1] == '>' && rl[i + 2] == '>')
		return (-1);
	else if (rl[i] == '>' && rl[i + 2] == '>')
		return (-1);
	else if (rl[i] == '<' && rl[i + 2] == '<')
		return (-1);
	else if (rl[i] == '|' && rl[i + 1] == '|' && rl[i + 2] == '|')
		return (-1);
	else if (rl[i] == '|')
	{
		i++;
		while (rl[i] == ' ')
		{
			i++;
			if (rl[i] == '|')
				return (-1);
		}
	}
	return (0);
}

int	check_error(char *rl)
{
	int	i;

	i = 0;
	if (rl != NULL && *rl == '\0')
		return (0);
	if (check_quote_close(rl) == -1)
		return (-1);
	if ((rl[i] == '>' || rl[i] == '<') && !rl[i + 1])
		return (-1);
	if (rl[i] == '|' || rl[i] == ':' || rl[i] == '!')
		return (-1);
	while (rl[i])
		i++;
	if (rl[i - 1] == '>' || rl[i - 1] == '<' || rl[i - 1] == '|')
		return (-1);
	i = 0;
	while (rl[i])
	{
		if (rl[i] == 34 || rl[i] == 39)
		{
			i++;
			while (rl[i] != 34 && rl[i] && rl[i] != 39)
				i++;
		}
		if (check_rl(rl, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	free_words_and_temp_args(char **temp_args, char **words)
{
	int	i;
	int	num_w;

	i = -1;
	while (temp_args[++i] != NULL)
		free(temp_args[i]);
	free(temp_args);
	temp_args = NULL;
	num_w = -1;
	while (words[++num_w] != NULL)
		free(words[num_w]);
	free(words);
	words = NULL;
}

int	fill_all_tab(t_data *da, char **words, char **temp_args, int i)
{
	int	num_w;

	num_w = 0;
	while (words[num_w] != NULL)
		num_w++;
	da->args[i] = malloc((num_w + 1) * sizeof(char *));
	if (da->args[i] == NULL)
		return (1);
	da->args[i][0] = fill_cmd(words);
	if (da->args[i][0])
		da->args[i][1] = NULL;
	da->pos_cmd = pos_cmd(words);
	da->io_nb = 0;
	fill_args_tab(da, words, i);
	fill_intab(da, temp_args[i], i);
	fill_outab(da, temp_args[i], i);
	return (0);
}

void	free_words(char **words)
{
	int	j;

	j = 0;
	while (words[j])
	{
		free (words[j]);
		j++;
	}
	free (words);
	words = NULL;
}

void	free_temp_args(char **temp_args)
{
	int	j;

	j = 0;
	while (temp_args[j])
	{
		free (temp_args[j]);
		j++;
	}
	free (temp_args);
	temp_args = NULL;
}

int	parsing(char *rl, t_data *da)
{
	char	**temp_args;
	char	**words;
	int		i;	

	i = 0;
	temp_args = NULL;
	words = NULL;
	temp_args = init_temp_args(rl, da);
	if (temp_args == NULL)
		return (printf ("Error: malloc failed\n"), 1);
	if (init_malloc(temp_args, da) == 1)
	{
		free_words_and_temp_args(temp_args, words);
		return (1);
	}
	while (i < da->pnum)
	{
		temp_args[i] = sup_tab(temp_args[i]);
		if (!temp_args[i])
			return (1);
		words = init_words(temp_args, i);
		if (!words)
			return (1);
		if (fill_all_tab(da, words, temp_args, i) == 1)
			return (printf("Error: malloc failed\n"), 1);
		free_words(words);
		i++;
	}
	free_temp_args(temp_args);
	// print_args(i, da->pnum, da);
	return (0);
}

void	if_sig(t_data *da)
{
	signal(SIGINT, sigint_handler_main);
	signal(SIGQUIT, SIG_IGN);
	if (g_stop_execution == 1)
	{
		g_stop_execution = 0;
		da->exit_status = 130;
	}
}

void	if_rl(char *rl, t_data *da, char **envp)
{
	if (parsing(rl, da) == 1)
		free_struct(da);
	else
	{
		if (!(heredoc_replace(da, 0, 0) == -1))
		{
			//signal(SIGINT, sigint_handler_main);
			//print_args(0, da.pnum, &da);
			if (da->pnum > 0)
				main_exec(da, envp);
		}
	}
	free_struct(da);
	add_history(rl);
}

int	main(int argc, char **argv, char **envp)
{
	char			*rl;
	t_data			da;
	int				i;

	(void)envp;
	if (argc != 1 || argv[0][0] == '\0')
		printf("ERROR\n");
	set_all(&da, envp, 0);
	set_parse(&da);
	while (1)
	{
		if_sig(&da);
		rl = readline("\033[1;36m<3 \033[0;37m");
		if (g_stop_execution == 1)
		{
			g_stop_execution = 0;
			da.exit_status = 130;
		}
		if (!rl)
		{
			write(1, "exit\n", 5);
			i = -1;
			while (da.my_env[++i] != NULL)
				free(da.my_env[i]);
			free(da.my_env);
			break ;
		}
		if (check_error(rl))
		{
			da.exit_status = 2;
			write(2, "parse error\n", 12);
			add_history(rl);
			continue ;
		}
		if (rl && *rl != '\0')
			if_rl(rl, &da, envp);
		free(rl);
	}
	return (0);
}
