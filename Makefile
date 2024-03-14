NAME			=	minishell

SRCS			=	main.c \
					main_exec.c \
					exec_utils.c \


OBJS			=	$(addprefix .build/, $(SRCS:.c=.o))

LD_FLAGS		=	-L libft

HEAD			=	-I includes -I libft

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra

.build/%.o: srcs/%.c
					@mkdir -p .build
					@$(CC) $(CFLAGS) -lreadline -lhistory $(HEAD) -c $< -o $@ 

$(NAME)			:	${OBJS}
					@echo "\033[0;33m\nCOMPILING LIBFT...\n"
					@make -sC libft
					@echo "\033[1;32mLIBFT_lib created\n"
					@echo "\033[0;33m\nCOMPILING MINISHELL...\n"
					@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME} -lreadline -lhistory -lft 
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