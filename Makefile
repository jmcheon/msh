NAME = minishell

INCLUDE = ./minishell.h

SRCS = main.c \
	./ft_strjoin.c \
	./ft_strjoin_memdel.c \
	./ft_strjoin_2dim.c \
	./ft_strjoin_2dim_memdel.c \
	./ft_strlen.c \
	./ft_strlen_2dim.c \
	./ft_memdel.c \
	./ft_memdel_2dim.c \
	./ft_strdup.c \
	./ft_strdup_2dim.c \
	./ft_strchr.c \
	./ft_strstr.c \
	./ft_substr.c \
	./ft_split.c \
	./ft_strcmp.c \
	./ft_strncmp.c \
	./ft_isalnum.c \
	./check_valid_quotes.c \
	./check_pipeline.c \
	./check_readline_argc.c \
	./check_valid_pipeline.c \
	./check_valid_redirection_n.c \
	./get_next_line.c \
	./init.c \
	./omit_character.c \
	./execute.c \
	./parse_pipe.c \
	./run_process.c \
	./run_command.c \
	./check_syntax.c \
	./redirection_input.c \
	./redirection_output.c \
	./split_character.c \
	./split_string.c \
	#./ft_execve.c \

OBJS = $(SRCS:.c=.o)

CC = clang

SAM = -fsanitize=address -g

#CFLAGS = -Wall -Wextra -Werror

RM = /bin/rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) -I $(INCLUDE) -L/usr/include -lreadline

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
