NAME = philo
DEST_DIR = dist/


# Main logic of the program: dir and filenames.
MAIN_DIR = srcs/
MAIN = main philosopher parser print utils error check# Main file of the program.

SRC = $(addsuffix .c, $(addprefix $(MAIN_DIR), $(MAIN))) \


OBJ = $(SRC:c=o)

FLAGS = -Wall -Werror -Wextra -pthread -g -g3 -fsanitize=thread 

%.o: %.c
	@${CC} ${FLAGS} -c $< -o $@  ${CPPFLAGS}

RM = rm -rf

CC = gcc

all: $(DEST_DIR)$(NAME)

$(DEST_DIR)$(NAME): $(OBJ)
	@echo "-----COMPILATION START-----"
	@echo "Compiling $(NAME)..."
	@$(CC)  $(FLAGS) $(OBJ)  -o $(DEST_DIR)$(NAME)
	@echo "Done."
	@echo "Execute ./$(DEST_DIR)$(NAME) to start the program."

debug: $(OBJ)
	@echo "-----COMPILATION DEBUG START-----"
	@echo "Compiling $(NAME)..."
	@$(CC) $(FLAGS) -g  $(OBJ)  -o $(DEST_DIR)$(NAME) -lreadline ${LDFLAGS} ${CPPFLAGS}
	@echo "Done."
	@echo "Execute ./$(DEST_DIR)$(NAME) to start the program."

clean:
	@echo "-----CLEANING START-----"
	@echo "Cleaning stuff for $(NAME)..."
	@echo "Cleaning objects..."
	@$(RM) $(OBJ)
	@echo "Cleaning objects Done."

fclean: clean
	@echo "Cleaning $(NAME) executable..."
	@$(RM) $(DEST_DIR)$(NAME)
	@echo "Cleaning $(NAME) executable Done."

run: all
	@echo "-----RUNNING START-----"
	@echo "Running $(NAME)..."
	@./$(DEST_DIR)$(NAME)

re: fclean all

crun: fclean all run

.PHONY: all clean fclean re 