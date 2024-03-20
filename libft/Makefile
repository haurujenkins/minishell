CC = cc
NAME = libft.a
SRC = ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strncpy.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_charrchr.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		get_next_line.c \
		char_print.c \
		ft_printf.c \
		str_print.c \
		int_print.c \
		hex_print.c \
		uint_print.c \
		hex_lower_print.c \
		my_strchr.c \
		hex_upper_print.c \
		ft_split_file.c
SRC_BONUS = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstsize_bonus.c
OBJ = $(addprefix .build/, $(SRC:.c=.o))
OBJ_BONUS = $(SRC_BONUS:.c=.o) 
FLAGS = -Wall -Werror -Wextra

.build/%.o : %.c libft.h
	mkdir -p .build
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)

all : $(NAME)

bonus : $(OBJ_BONUS) libft.h
	ar rc $(NAME) $(OBJ_BONUS)

clean :
	rm -rf ${OBJ}
	rm -rf .build

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY:		all clean fclean re bonus