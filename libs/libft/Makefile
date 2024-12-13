# Print message at the very beginning
.DEFAULT_GOAL	:=	print_message

print_message:	
	@printf "\033[99D\033[J\033[1;34m****** Entering in libft ******\n"
	@$(MAKE) main_target --no-print-directory

NAME		= 	libft.a

CC			= 	gcc
FLAGS		= 	-c -Wall -Wextra -Werror

ARCHIVE		= 	ar rc
RANLIB		= 	ranlib
INC		    =	-I./includes
SRCS		=	$(shell find . -maxdepth 1 -name "*.c" | rev | cut -d '/' -f1 |\
				rev)

OBJS_DIR	=	./obj/
OBJS		=	$(addprefix $(OBJS_DIR), $(shell find $(OBJS_DIR)\
				-name "*.o" | rev | cut -d '/' -f1 | rev))
OBJECTS		=	$(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS))

main_target: all

all: $(NAME)

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@


$(NAME): $(OBJECTS)
	@printf "\033[99D\033[J\033[38;5;214mGenerating archive from objects libft.a\n"
	@$(ARCHIVE) $(NAME) $(OBJS)
	@printf "\033[99D\033[J\033[38;5;214mGenerating index from libft.a\n"
	@$(RANLIB) $(NAME)
	@printf "\033[99D\033[J\033[0;32m$(NAME): Done!!\n"

.PHONY: all clean fclean

clean:
	@printf "\033[99D\033[J\033[31mRemoving libft objects\n"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@printf "\033[99D\033[J\033[31mremoving $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re print_message main_target