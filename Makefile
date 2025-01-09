# Print message at the very beginning
.DEFAULT_GOAL	:=	print_message

print_message:	
	@printf "\033[99D\033[J\033[1;34m****** Start Compiling ******\n"
	@$(MAKE) --no-print-directory main_target

# Variables
NAME		=ft_ls
SRC_PATH	=./srcs/
OBJ_PATH	=./obj/
SRCS		=$(addprefix $(SRC_PATH), $(shell find ./srcs -maxdepth 1 -name "*.c" | rev | cut -d '/' -f1 |\
				rev))#main.c# Add all your source files here
OBJS		=$(SRCS:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
COMP_FLAG	=-Wall -Wextra -Werror
INC			=-I ./includes -I ./libs/libft/includes -I ./libs/ft_printf/includes# Add your include paths here
LIB_PATH	=-L ./libs/libft -L ./libs/ft_printf# Add your library paths here
LIB			=-lft_printf -lft# Add your libraries here
PATHS		=./libs/# Adjust the path to your libraries

main_target: all
# Default target
all:$(NAME)

# Link the final executable
$(NAME):$(OBJS)
	@printf "\033[99D\033[J\033[38;5;214mCompiling libft library\n"
	@make -C $(PATHS)libft/ --no-print-directory
	@printf "\033[99D\033[J\033[38;5;214mCompiling libft_printf library\n"
	@make -C $(PATHS)ft_printf/ --no-print-directory
	@printf "\033[99D\033[J\033[38;5;214mCompiling $(NAME)\n"
	@gcc $(COMP_FLAG) $(OBJS) $(INC) $(LIB_PATH) $(LIB) -o $(NAME)
	@printf "\033[99D\033[J\033[0;32mWork Complete!!! -> Usage: $(NAME) [OPTION]... [FILE]...\n\033[m"

# Compile object files
$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@gcc $(COMP_FLAG) $(INC) -o $@ -c $<

# Clean target
clean:
	@printf "\033[99D\033[J\033[31mWARNING: Partial Removing objects:\n"
	@printf "\033[99D\033[J\033[31m\t- libft objects\n"
	@make -C $(PATHS)libft/ clean > --no-print-directory
	@printf "\033[99D\033[J\033[31m\t- ft_printf objects\n"
	@make -C $(PATHS)ft_printf/ clean --no-print-directory
	@printf "\033[99D\033[J\033[31mRemoving objects:\n"
	@printf "\033[99D\033[J\033[31m\t- file objects:\n"
	@rm -rf $(OBJ_PATH) > /dev/null 2>&1
	@printf "\033[99D\033[J\033[0;32mCleaning done\n"

# Full clean target
fclean:
	@printf "\033[99D\033[J\033[1;31m*** WARNING: Full Removing ***\n"
	@make -C $(PATHS)libft fclean --no-print-directory
	@make -C $(PATHS)ft_printf fclean --no-print-directory
	@printf "\033[99D\033[J\033[31mRemoving main Objects\n"
	@rm -rf $(OBJ_PATH) > /dev/null 2>&1
	@printf "\033[99D\033[J\033[31mRemoving main Binaries\n"
	@rm -fv $(NAME) > /dev/null 2>&1
	@printf "\033[99D\033[J\033[0;32mForce cleaning done\n"

# Rebuild target
re:	fclean all

.PHONY:	all clean fclean re print_message