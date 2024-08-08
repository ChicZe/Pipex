# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 16:45:11 by ciusca            #+#    #+#              #
#    Updated: 2024/04/24 16:18:18 by ciusca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_B = pipex_bonus

SRC = pipex.c parsing.c check_execve.c
BONUS_SRC = pipex_bonus.c parsing_bonus.c check_execve_bonus.c

OBJ = $(addprefix src/, $(SRC:.c=.o))
BONUS_OBJS = $(addprefix bonus_src/, $(BONUS_SRC:.c=.o))

COMPILE = cc -Wall -Wextra -Werror -g

LIBFT_PATH = libft
LIBFT_A = libft.a
LIBFT = libft/libft.a

RED = "\033[1;31m"
GREEN = "\033[1;32m"
YELLOW = "\033[1;33m"
BLUE = "\033[1;34m"
MAGENTA = "\033[1;35m"
CYAN = "\033[1;36m"
WHITE = "\033[1;37m"
NONE = '\033[0m'

all: $(NAME)

%.o: %.c
		$(COMPILE) -I $(LIBFT_PATH) -c $< -o $@

$(NAME): $(OBJ)
		make bonus -C $(LIBFT_PATH)
		$(COMPILE) $(OBJ) $(LIBFT) -o $(NAME)
		@echo $(CYAN) " _____ ___________ _______   __ " $(NONE)
		@echo $(MAGENTA) "| ___ \_   _| ___ \  ___\ \ / / " $(NONE)
		@echo $(BLUE) "| |_/ / | | | |_/ / |__  \ V /  " $(NONE)
		@echo $(BLUE) "|  __/  | | |  __/|  __| /   \  " $(NONE)
		@echo $(MAGENTA) "| |    _| |_| |   | |___/ / \ \ " $(NONE)
		@echo $(CYAN) "\_|    \___/\_|   \____/\/   \/ " $(NONE)
		@echo $(WHITE) "\n\n\nHow it works:" $(YELLOW) "./pipex infile cmd cmd2 outfile \n\n\n" $(NONE)

bonus: $(NAME_B)

%.o: %.c
	$(COMPILE) -I $(LIBFT_PATH) -c $< -o $@

$(NAME_B): $(BONUS_OBJS)
	make bonus -C $(LIBFT_PATH)
	$(COMPILE) $(BONUS_OBJS) $(LIBFT) -o $(NAME_B)
	@echo $(CYAN) " _____ ___________ _______   __ " $(NONE)
	@echo $(MAGENTA) "| ___ \_   _| ___ \  ___\ \ / / " $(NONE)
	@echo $(BLUE) "| |_/ / | | | |_/ / |__  \ V /  " $(NONE)
	@echo $(BLUE) "|  __/  | | |  __/|  __| /   \  " $(NONE)
	@echo $(MAGENTA) "| |    _| |_| |   | |___/ / \ \ " $(NONE)
	@echo $(CYAN) "\_|    \___/\_|   \____/\/   \/ " $(NONE)
	@echo $(WHITE) "\n\n\nThis is the bonus part:" $(YELLOW) "it can handle n commands and here_doc\n" $(NONE)
	@echo $(WHITE) "-------------------------------\\n\n" $(NONE)
	@echo $(GREEN) "The program is called: pipex_bonus\n" $(NONE)

clean:
	@rm -rf $(OBJ)
	@rm -rf $(BONUS_OBJS)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(OBJS) $(BONUS_OBJS) $(NAME) $(NAME_B)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re

.SILENT: