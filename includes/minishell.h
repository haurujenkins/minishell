/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:48:53 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/14 16:52:18 by abolea           ###   ########.fr       */
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
# include <sys/stat.h>
# include "../libft/libft.h"
#include <termios.h>
# define MAX_INPUT_LENGTH 1024

extern volatile sig_atomic_t ctrl_c_flag;

typedef struct s_signals
{
	char	*endof;
	int		nb_delim;
	int		exit;
	int		heredoc;
}			t_signals;


typedef struct data_s
{
	int			i;
	int			j;
	int			line;
	int			out;
	char		**my_env;
	char		**cmd1;
	char		**my_path;
	char		*cmd;
	char		*point_path;
	int			fd_input;
	int			fd_output;
	int			fail_pipe;
	int			**pipefd;
	pid_t		pid1;
	pid_t		pid2;
	int			pnum;
	char		***args;
	char		***in_tab;
	char		***out_tab;
	int			p_in;
	int			p_out;
	int			check_export;
	int			exit_status;
	char		***delim_tab;
	char		***append_tab;
	int			nb_redir_in;
	int			nb_redir_out;
	int			io_nb;
	int			i_in_quotes;
	int			o_in_quotes;
	int			nb_delim;
	int			in_delim;
	int			o_append;
	int			nb_append;
	char		***args_tab;
	int			nb_args;
	int			i_args;
	int			pos_cmd;
	char		**words;
	t_signals	mysignal;
}				t_data;

void	get_args(t_data *da, char **envp, int index);
void	set_pipe(t_data *da);
int		main_exec(t_data *da, char **envp);
int		check_files(t_data *da, int index);
void	exec_cmd(t_data *da, char **envp);
void	set_all(t_data *da, char **envp);
void	free_data(t_data *da, char **envp);
int		check_builtins(t_data *da);
int		check_extern_builtins(t_data *da, char **env, int index);
char	*get_home(char **envp);
void	close_fd(t_data *da, int index);
int		ft_tablen(char **tab);
char	**ft_realloc(char **tab, int size);
int		get_args_builtins(t_data *da, int index);
void	my_cd(char **cmd, char **envp, t_data *da);
void	my_pwd(void);
void	my_echo(char **cmd);
void	my_env(char **env, int num, int j);
void	my_export(t_data *da);
void	my_unset(t_data *da);
void	sort_env(t_data *da);
void	free_pipe(t_data *da);
void	free_struct(t_data *da);
void	export_pwd(t_data *da, char *temp_value);
void	infile_error(t_data *da, int index, int i);
char	*read_until_delimiter(char *delimiter, t_data *da);
void	outfile_error(t_data *da, int index, int i);
void	check_infile(t_data *da, int index);
void	check_outfile(t_data *da, int index);
void	exit_free(t_data *da);
void	sigint_handler(int signum);
void	set_flag(void);
int		heredoc_replace(t_data *da, int index);
void	del_tmpfiles(t_data *da, int index);

void	print_args(int i, int pnum, t_data *da);
void	loading(int p);
void	print_title();
void	print_all();
int		ft_nb_redir(char *temp_args, char c);
int		fill_append_tab(t_data *da, char **temp_args);
char	*sup_append(char *s);
int		len_without_append(char *s);
int		fill_delim_tab(t_data *da, char **temp_args);
char	*sup_delim(char *s);
char	*cpy_until_char(char *s, char c, int start);
int		if_finish_quotes(char *s);
int		if_finish_squotes(char *s);
void	fill_outab(t_data *da, char *temp_args, int i);
void	fill_intab(t_data *da, char *temp_args, int i);
void	if_quotes_not_close(char **temp_args, int i);
int		if_io_before_last_quotes(char *s, char c, int start);
int		if_quotes(char *s, int start);
char	*cpy_args_without_quotes(char *s);
char	*fill_args(t_data *da, char **words, int i);
char	*fill_cmd(char **words);
char	**new_temp_args(t_data *da, char **temp_args);
int		nb_pipe(char *rl);
int		nb_io(char *s);
int		nb_quotes(char *s);
int		if_dollar(char *s);
int		len_env(t_data *da, char *s);
char	*find_in_env(t_data *da, char *s);
char	*after_dollar(char *s);
char	*temp_without_dollar(t_data *da, char *temp_args);
char	*get_cmd(char *words);
int		len_cmd(char *words);
int		double_quotes_close(char *temp_args);
char	*cpy_for_args(char *s, int start);
int		len_for_args(char *s, int start);
void	fill_args_tab(t_data *da, char **temp_args, int i);
int		pos_cmd(char **words);
char	*cpy_args_without_s_quotes(char *s);
char	*new_temp(char *s);
int		nb_dollars(char *s);
char	*all_positive(char *s);
char	*negative_in_quotes(char *s);
char	*dollar_negative_in_s_quote(char *s);
char	**init_words(char **temp_args, int i);
char	**init_temp_args(char *rl, t_data *da);
int		init_malloc(char **temp_args, t_data *da);

#endif