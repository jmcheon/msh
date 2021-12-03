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
	./ft_substr_2dim.c \
	./ft_strdup.c \
	./ft_strdup_by_index.c \
	./ft_strdup_2dim.c \
	./ft_strchr.c \
	./ft_strstr.c \
	./ft_strtrim_2dim.c \
	./ft_strtrim_2dim_by_index.c \
	./ft_substr.c \
	./ft_split.c \
	./ft_strcmp.c \
	./ft_strncmp.c \
	./ft_isalnum.c \
	./ft_isalpha.c \
	./ft_itoa.c \
	./ft_itos.c \
	./ft_putendl_fd.c \
	./ft_putstr_fd.c \
	./malloc_funcs.c \
	./check_syntax_n.c \
	./check_quotes_n.c \
	./check_pipeline_n.c \
	./check_valid_redirection_n.c \
	./check_redirection_variable.c \
	./check_token.c \
	./get_next_line.c \
	./init.c \
	./omit_quotes_n.c \
	./execute.c \
	./parse_pipe_n.c \
	./parse_redirection_part_n.c \
	./run_process_n.c \
	./run_command_n.c \
	./run_child_pipe_commands.c \
	./run_one_command_n.c \
	./redirection_input.c \
	./redirection_output.c \
	./check_readline_argc_n.c \
	./split_character_n.c \
	./split_string_n.c \
	./split_readline_n.c \
	./rmalloc_line.c \
	./get_next_line_size.c \
	./check_variable_n.c \
	./replace_variables_one_line.c \
	./search_one_variable.c \
	./ft_execve.c \
	./ft_cd.c \
	./ft_unset.c \
	./ft_exit.c \
	./ft_echo.c \
	./ft_pwd.c \
	./ft_env.c \
	./ft_export.c \
	./ft_setenv.c \
	./signal.c \
	#./check_readline_argc.c \
	./check_valid_pipeline.c \
	./check_redirection.c \

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

norm : 
	norminette $(SRCS) #$(INCLUDE)

.PHONY : all clean fclean re norm
