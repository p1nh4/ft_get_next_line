NAME 		:= get_next_line.a
CC 	 		:=	cc
C_FLAGS		:= -Wall -Wextra -Werror
AR			:= ar
AR_FLAGS 	:= -rcs
OBJ_DIR		:= obj
SRC_INCLUDE	:= get_next_line.h \
			   get_next_line_bonus.h
SRC			:= get_next_line.c		\
			   get_next_line_utils.c
SRC_BONUS	:= get_next_line_bonus.c \
			   get_next_line_utils_bonus.c
#INCLUDES	:= -I$(SRC_INCLUDE)
OBJ			:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_BONUS       := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_BONUS))
RM			:= rm -f

#TEST 		:= test_gnl
#TEST_BONUS	:= test_bonus

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(AR_FLAGS) $@ $^

bonus : .bonus

.bonus : $(OBJ_BONUS)
	$(AR) $(AR_FLAGS) $(NAME) $^
	@touch .bonus

$(OBJ_DIR)/%.o : %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) -c -o $@ $<

#test: $(OBJ) testes/test_main.c
#	$(CC) $(C_FLAGS) -D BUFFER_SIZE=42 $(OBJ) testes/test_main.c -o $(TEST) ./$(TEST)

#test_bonus: $(OBJ_BONUS) testes/test_bonus.c
#	$(CC) $(C_FLAGS) -D BUFFER_SIZE=42 $(OBJ_BONUS) testes/test_bonus.c -o $(TEST_BONUS) ./$(TEST_BONUS)

clean :
	$(RM) $(OBJ) $(OBJ_BONUS) .bonus #$(TEST) $(TEST_BONUS)

fclean : clean
	$(RM) $(NAME)
	$(RM) -r $(OBJ_DIR)

re : fclean all

.PHONY : all bonus clean fclean re #test test_bonus

