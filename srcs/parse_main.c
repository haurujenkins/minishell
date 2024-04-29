/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/04/29 15:21:31 by lle-pier         ###   ########.fr       */
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

int	parsing(char *rl, t_data *da)
{
	char	**temp_args;
	char	**words;
	int		i;
	int		num_w;	

	i = 0;
	temp_args = NULL;
	words = NULL;
	da->pnum = nb_pipe(rl);
	num_w = 0;
	temp_args = ft_split(rl, '|');
	if (temp_args == NULL)
		return (printf ("Error: malloc failed\n"), 1);
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
	while (i < da->pnum)
	{
		if_quotes_not_close(temp_args, i);
		//after_dollar(temp_args[i]);
		words = ft_split(temp_args[i], ' ');
		while (words[num_w] != NULL)
			num_w++;
		da->args[i] = malloc((num_w + 1) * sizeof(char *));
		if (da->args[i] == NULL)
			return (printf("Error: malloc failed\n"), 1);
		da->args[i][0] = fill_cmd(words);
		da->args[i][1] = NULL;
		da->pos_cmd = pos_cmd(words);
		da->io_nb = 0;
		i++;
	}
	fill_args_tab(da, words);
	fill_intab(da, temp_args);
	fill_outab(da, temp_args);
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
	// print_all();
	while (1)
	{
		rl = readline("\033[1;36m<3 \033[0;37m");
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
				// free_struct(&da);
			}
			else
			{
				add_history(rl);
				free(rl);
				main_exec(&da, envp);
				// free_struct(&da);
			}
		}
	}
	return (0);
}
