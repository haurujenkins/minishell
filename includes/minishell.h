/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:48:53 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/04 16:43:06 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct data_s
{
	int		i;
	int		j;
	int		line;
	int		out;
	char	**cmd1;
	char	**cmd2;
	char	**my_path;
	char	*cmd;
	char	*point_path;
	int		fd_input;
	int		fd_output;
	int		fail_pipe;
	int		**pipefd;
	pid_t	pid1;
	pid_t	pid2;
	int		pnum;
	char	***args;
	char	***in_tab;
	char	***out_tab;
	int		nb_redir_in;
	int		nb_redir_out;
	int		p_in;
	int		p_out;
}				t_data;

void	get_args(t_data *da, char **envp, int index);
void	set_pipe(t_data *da);
int		main_exec(t_data *da, char **envp);
int		check_files(t_data *da, int index);
void	exec_cmd(t_data *da, char **envp, int index);
void	set_all(t_data *da);
void	free_data(t_data *da, char **envp);

#endif