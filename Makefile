# EXECUTABLE
NAME =so_long

# LIBRARIES
LIBFT = $(LIB_DIR)libft.a
MINILIBX = $(LIB_DIR)libmlx.a

# DIRECTORIES
SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = lib/
INC_DIR = inc/

# COMPILE STUFF
CC = gcc
CFLAGS = -I$(INC_DIR) -I$(LIB_DIR)libft -I$(LIB_DIR)minilibx-linux -Wall -Werror -Wextra
LINKS = -L$(LIB_DIR) -lft -lmlx -lX11 -lXext -lm

# FILES
SRC_FILES = main.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# HEADER FILES
HEADERS = $(wildcard $(INC_DIR)*.h)

# RULES
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	@echo "Preparing the executable..."
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LINKS)
	@echo "\nso_long is ready.\nUsage: ./so_long map_path"

$(LIBFT):
	@echo "Creating libft.a..."
	@make --silent -C $(LIB_DIR)libft
	@cp $(LIB_DIR)libft/libft.a $@

$(MINILIBX):
	@echo "Creating libmlx_Linux.a..."
	@make --silent -C lib/minilibx-linux > /dev/null 2>&1
	@cp lib/minilibx-linux/libmlx.a $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning!"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR)libft clean
	@make -C $(LIB_DIR)minilibx-linux clean

fclean: clean
	@echo "Full cleaning!"
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@rm -f $(MINILIBX)
	@make -C $(LIB_DIR)libft fclean

re: fclean all

.PHONY: all clean fclean re