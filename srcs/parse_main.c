/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/05/30 15:09:10 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (fill_args_tab(da, words, i) == 1)
		return (1);
	if (fill_intab(da, temp_args[i], i) == 1)
		return (1);
	if (fill_outab(da, temp_args[i], i) == 1)
		return (1);
	return (0);
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
	{
		da->exit_status = 134;
		free_struct(da);
	}
	else
	{
		if (!(heredoc_replace(da, 0, 0) == -1))
		{
			if (da->pnum > 0)
			{
				if (main_exec(da, envp) == -1)
					da->exit_status = 134;
			}
		}
	}
	free_struct(da);
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
		rl = readline("\001\033[1;36m\002<3 \001\033[0;37m\002");
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
		if (rl[0])
			add_history(rl);
		if (rl && *rl != '\0')
			if_rl(rl, &da, envp);
		free(rl);
	}
	return (0);
}
