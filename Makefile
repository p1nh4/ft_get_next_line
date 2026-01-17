NAME 		:= get_next_line.a
CC 	 		:=	cc
C_FLAGS		:= -Wall -Wextra -Werror
AR			:= ar
AR_FLAGS 	:= -rcs
OBJ_DIR		:= obj
SRC_INCLUDE	:= get_next_line.h
SRC			:= get_next_line.c		\
			   get_next_line_utils.c
#INCLUDES	:= -I$(SRC_INCLUDE)
OBJ			:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
RM			:= rm -f

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(AR_FLAGS) $@ $^

$(OBJ_DIR)/%.o : %.c get_next_line.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) $(INCLUDES) -c -o $@ $<

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)
	$(RM) -r $(OBJ_DIR)

re : fclean all

.PHONY : all clean fclean re

