NAME			=	minishell

SRCS			=	parse_main.c \
					exec_main.c \
					exec_utils.c \
					exec_get_args.c \
					exec_pipe.c \
					exec_files.c \
					exec_handlers.c \
					exec_builtins.c \
					exec_builtins_utils.c \
					exec_check_builtins.c \
					exec_builtins_cases.c \
					exec_export.c \
					exec_export_errors.c \
					exec_export_oldpwd.c \
					exec_check_files.c \
					exec_check_stat.c \
					exec_heredoc.c \
					exec_heredoc_read.c \
					exec_check_cmd.c \
					exec_free.c \
					parse_append.c \
					parse_utils.c \
					parse_delim.c \
					parse_fillout.c \
					parse_fillin.c \
					parse_quote.c \
					parse_fill_args.c \
					parse_nb.c \
					parse_dollar.c \
					parse_env.c \
					parse_new_temp.c \
					parse_modif_rl.c \
					parse_init.c \
					parse_fill_cmd.c \
					parse_sup_space.c \
					parse_quotes_dollar.c \
					parse_nb_args.c \
					parse_nb_append_delim.c \
					parse_free.c \
					parse_expand.c \
					parse_expand_quotes.c \
					parse_dollar_heredoc.c \
					parse_cpy_expand.c \
					parse_cpy_args.c \
					parse_check_error.c \
					parse_check_args.c \
					parse_args_quotes.c \
					parse_check_rl.c \
					parse_fill_all_tab.c


OBJS			=	$(addprefix .build/, $(SRCS:.c=.o))

LD_FLAGS		=	-L libft

HEAD			=	-I includes -I libft

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra

HEREDOC_DIR		=	.heredoc

.build/%.o: srcs/%.c | ${HEREDOC_DIR}
					@mkdir -p .build
					@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@

${HEREDOC_DIR}:
					@mkdir -p ${HEREDOC_DIR}

$(NAME)			:	${OBJS}
					@echo "\033[0;33m\nCOMPILING LIBFT...\n"
					@make -sC libft
					@echo "\033[1;32mLIBFT_lib created\n"
					@echo "\033[0;33m\nCOMPILING MINISHELL...\n"
					@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME} -lreadline -lft 
					@echo "\033[1;32mMINISHELL created\n"
					

all				:	${NAME}

					valgrind \
					--leak-check=full --tool=memcheck \
					--show-reachable=yes \
					--track-fds=yes \
					--errors-for-leak-kinds=all \
					--show-leak-kinds=all ./${NAME}

clean			:
					@make clean -sC libft
					@rm -rf ${OBJS}
					@rm -rf .build

fclean			:	clean
					@make fclean -sC libft
					@echo "\033[1;32mCLEANED !\n"
					@rm -rf ${NAME}
					@rm -rf ${HEREDOC_DIR}

re				:	fclean all

.PHONY			:	all clean fclean re FORCE