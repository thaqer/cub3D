NAME 	= cub3D
CC   	= cc
CFLAGS 	= -Wall -Werror -Wextra

incDir 		= includes
objDir 		= obj
libftDir	= libft
LIBFT		= $(libftDir)/libft.a

GREEN   	= \033[0;32m
RED    		= \033[0;31m
RESET   	= \033[0m
ARROW   	= ✔

SRCS		= src/main.c \
			  src/init/initialize.c \
			  src/init/parsing.c \
			  src/gnl/get_next_line.c \
			  src/gnl/get_next_line_utils.c \
			  src/end/end.c \
			  src/debugging.c

OBJS		= $(SRCS:%.c=$(objDir)/%.o)

all: $(NAME)

$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make --no-print-directory -C $(libftDir)
	@echo "$(GREEN)libft built $(ARROW)$(RESET)"

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)Making $(NAME)...$(RESET)"
	@$(CC) -o $(NAME) $(OBJS) -L$(libftDir) -lft
	@echo "$(GREEN)Done $(ARROW)$(RESET)"
	
$(objDir)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(incDir) -c $< -o $@

clean:
	@echo "$(RED)Deleting $(objDir)...$(RESET)"
	@rm -rf $(objDir)
	@make --no-print-directory -C $(libftDir) clean
	@echo "$(RED)Done $(ARROW)$(RESET)"

fclean: clean
	@echo "$(RED)Deleting $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make --no-print-directory -C $(libftDir) fclean
	@echo "$(RED)Done $(ARROW)$(RESET)"

re: fclean all

.PHONY: all clean fclean re