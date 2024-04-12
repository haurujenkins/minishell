/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:48:53 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/12 11:07:57 by abolea           ###   ########.fr       */
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
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct data_s
{
	int		i;
	int		j;
	int		line;
	int		out;
	char	**my_env;
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
	int		check_export;
	int		exit_status;
	char	***delim_tab;
	char	***append_tab;
	int		io_nb;
	int		i_in_quotes;
	int		o_in_quotes;
	int		nb_delim;
	int		in_delim;
	int		o_append;
	int		nb_append;
}				t_data;

void	get_args(t_data *da, char **envp, int index);
void	set_pipe(t_data *da);
int		main_exec(t_data *da, char **envp);
int		check_files(t_data *da, int index);
void	exec_cmd(t_data *da, char **envp, int i);
void	set_all(t_data *da, char **envp);
void	free_data(t_data *da, char **envp);
int		check_builtins(t_data *da);
int		check_extern_builtins(t_data *da, char **env, int index);
char	*get_home(char **envp);
void	close_fd(t_data *da, int index);
int		ft_tablen(char **tab);
char	**ft_realloc(char **tab, int size);
void	get_args_builtins(t_data *da, int index);
void	my_env(char **env, int num);
void	my_cd(char **cmd, char **envp, t_data *da);
void	my_pwd(void);
void	my_echo(char **cmd, t_data *da);
void	my_env(char **env, int num);
void	my_export(t_data *da);
void	my_unset(t_data *da);
void	sort_env(t_data *da);
void	free_pipe(t_data *da);
void	print_args(int i, int pnum, t_data *da);

void	loading(int p);
void	print_title();
void	print_all();

#endif