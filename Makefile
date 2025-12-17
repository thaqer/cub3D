NAME 	= cub3D
CC   	= cc
CFLAGS 	= -Wall -Werror -Wextra -g3


incDir 		= includes
objDir 		= obj
libftDir	= libft
LIBFT		= $(libftDir)/libft.a
MLXDir		= MLX42
MLX			= $(MLXDir)/build/libmlx42.a

GREEN   	= \033[0;32m
RED    		= \033[0;31m
RESET   	= \033[0m
ARROW   	= ✔

SRCS		= src/main.c \
			  src/init/initialize.c \
			  src/init/init_utils.c \
			  src/gnl/get_next_line.c \
			  src/run_game/run.c \
			  src/run_game/valid_move.c \
			  src/run_game/mouse_control.c \
			  src/run_game/dda.c \
			  src/run_game/movement.c \
			  src/run_game/render.c \
			  src/run_game/walls.c \
			  src/end/end.c \
			  src/debugging.c \
			  src/utils/init_utils.c \
			  src/parsing/parsing_utils.c\
			  src/parsing/parsing.c \
			  src/parsing/map_parsing.c \
			  src/parsing/map_parsing_utils.c \
			  src/parsing/map_parsing_helper.c \
			  src/parsing/line_utils.c \
			  src/parsing/map_validation.c \
			  src/parsing/color_validation.c \
			  src/parsing/textures_validation.c

OBJS		= $(SRCS:%.c=$(objDir)/%.o)

all: $(NAME)

$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make --no-print-directory -C $(libftDir)
	@echo "$(GREEN)libft built $(ARROW)$(RESET)"

$(MLX):
	@echo "$(GREEN)Building mlx...$(RESET)"
	@cmake -B $(MLXDir)/build $(MLXDir) > /dev/null 2>&1
	@cmake --build $(MLXDir)/build -j4 > /dev/null 2>&1
	@echo "$(GREEN)mlx built $(ARROW)$(RESET)"

$(NAME): $(LIBFT) $(MLX) $(OBJS) 
	@echo "$(GREEN)Making $(NAME)...$(RESET)"
	@$(CC) -o $(NAME) $(OBJS) -L$(libftDir) -lft  -L./$(MLXDir)/build -lmlx42 -ldl -lglfw -pthread -lm
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
	@rm -rf $(MLXDir)/build
	@make --no-print-directory -C $(libftDir) fclean
	@echo "$(RED)Done $(ARROW)$(RESET)"

re: fclean all

.PHONY: all clean fclean re