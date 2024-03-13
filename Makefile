NAME			=	minishell

SRCS			=	pipex.c \
					pipex_utils.c \
					pipex_utils_2.c

OBJS			=	$(addprefix .build/, $(SRCS:.c=.o))

LD_FLAGS		=	-L libft

HEAD			=	-I includes -I libft

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra

.build/%.o: srcs/%.c
					@mkdir -p .build
					@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@

$(NAME)			:	${OBJS}
					@echo "\033[0;33m\nCOMPILING LIBFT...\n"
					@make -sC libft
					@echo "\033[1;32mLIBFT_lib created\n"
					@sleep 0.5
					@echo "\033[0;33m\nCOMPILING MINISHELL...\n"
					@sleep 1
					@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME} -lft
					@echo "\033[1;32mMINISHELL created\n"
					

all				:	${NAME}

					valgrind \
					--leak-check=full --tool=memcheck \
					--show-reachable=yes \
					--track-fds=yes \
					--errors-for-leak-kinds=all \
					--show-leak-kinds=all ./${NAME} input cat cat output

clean			:
					@make clean -sC libft
					@rm -rf ${OBJS}
					@rm -rf .build

fclean			:	clean
					@make fclean -sC libft
					@echo "\033[1;32mCLEANED !\n"
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re