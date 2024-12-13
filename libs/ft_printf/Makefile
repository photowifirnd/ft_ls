# Print message at the very beginning
.DEFAULT_GOAL	:=	print_message

print_message:	
	@printf "\033[99D\033[J\033[1;34m****** Entering in ft_printf ******\n"
	@$(MAKE) main_target --no-print-directory

LIB_NAME	= 	libft_printf.a

ARCHIVE		= 	ar rc
RANLIB		= 	ranlib
CC			= 	gcc
FLAGS		= 	-Wall -Wextra -Werror
#Puedes hacer control z hasta este punto

INCLUDE_PATHS=	./includes ../libft/includes
INCLUDES	=	$(addprefix -I, $(INCLUDE_PATHS))

SRCS		=	$(shell find . -maxdepth 1 -name "*.c" | rev | cut -d '/' -f1 |\
				rev)

OBJS_DIR	=	./obj/
OBJS		=	$(addprefix $(OBJS_DIR), $(shell find $(OBJS_DIR)\
				-name "*.o" | rev | cut -d '/' -f1 | rev))
OBJECTS		=	$(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS))

main_target: all

all: $(LIB_NAME)

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIB_NAME): $(OBJECTS)
	@printf "\033[99D\033[J\033[38;5;214mGenerating archive from objects: ft_printf.a\n"
	@$(ARCHIVE) $(LIB_NAME) $(OBJS)
	@printf "\033[99D\033[J\033[38;5;214mGenerating index from ft_printf.a\n"
	@$(RANLIB) $(LIB_NAME)
	@printf "\033[99D\033[J\033[0;32m$(LIB_NAME): Work complete!\n"

.PHONY: all clean fclean

clean:
	@printf "\033[99D\033[J\033[31mRemoving ft_printf objects\n"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@printf "\033[99D\033[J\033[31mremoving $(LIB_NAME)\n"
	@rm -f $(LIB_NAME)

re: fclean all

.PHONY: all clean fclean re print_message main_target