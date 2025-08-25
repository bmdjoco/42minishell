# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 13:23:14 by bdjoco            #+#    #+#              #
#    Updated: 2025/08/25 16:10:22 by bdjoco           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_fprintf.a

SRC = ft_fprintf.c \
		ft_fprintf_types.c \
		ft_fprintf_types_utils.c \
		ft_fprintf_utils.c \
		utils.c

INC = ft_fprintf.h

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

BOLD = \e[1m
GREEN = \e[32m
PURPLE = \e[35m
RESET = \e[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(BOLD)$(NAME)$(RESET) $(GREEN)est compilé $(RESET)​🔰​"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "$(GREEN)Nettoyage des$(RESET) $(BOLD)fichiers source de ft_fprintf$(RESET) $(GREEN)terminé$(RESET) 🚮"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)Nettoyage de$(RESET) $(BOLD)$(NAME)$(RESET) $(GREEN)terminé$(RESET) 🚮"

re: fclean all

.PHONY : all clean fclean re bonus
