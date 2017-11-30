CC = gcc
NAME = libft.a
FLAGS= -Wall -Wextra -Werror
CHECKS= checks/ft_isalnum.c checks/ft_isalnumword.c checks/ft_isalpha.c checks/ft_isascii.c \
		checks/ft_isdigit.c checks/ft_isnumber.c checks/ft_isprint.c checks/ft_isspace.c
DISPLAY= display/ft_putchar.c display/ft_putchar_fd.c display/ft_putendl.c display/ft_putnbr.c \
		 display/ft_putnbr_fd.c display/ft_putstr.c display/ft_putstr_fd.c display/ft_putendl_fd.c\
		 display/ft_putnbrendl.c
LST= lst/ft_count_lst.c lst/ft_lstadd.c lst/ft_lstaddend.c lst/ft_lstdel.c lst/ft_lstdelone.c \
	 lst/ft_lstiter.c lst/ft_lstmap.c lst/ft_lstnew.c lst/lst_add.c
MEM= mem/ft_bzero.c mem/ft_memalloc.c mem/ft_memchr.c mem/ft_memcmp.c mem/ft_memcpy.c mem/ft_memdel.c\
	 mem/ft_memmove.c mem/ft_memset.c mem/ft_memccpy.c
MISC= misc/ft_atoi.c misc/ft_itoa.c misc/ft_range.c misc/ft_sqrt.c misc/ft_swap.c misc/ft_tab_size.c\
	  misc/ft_tolower.c misc/ft_toupper.c misc/ft_whitespace.c misc/get_next_line.c misc/ft_wordtab_to_str.c
STR= str/ft_str_epur.c str/ft_strcat.c str/ft_strchr.c str/ft_strclr.c str/ft_strcmp.c str/ft_strcpy.c\
	 str/ft_strcut.c str/ft_strdel.c str/ft_strdup.c str/ft_strequ.c str/ft_striter.c str/ft_striteri.c\
	 str/ft_strjoin.c str/ft_strjoin_free.c str/ft_strjoin_free_one.c str/ft_strlcat.c str/ft_strlen.c\
	 str/ft_strmap.c str/ft_strmapi.c str/ft_strncat.c str/ft_strncmp.c str/ft_strncpy.c str/ft_strnequ.c\
	 str/ft_strnew.c str/ft_strnstr.c str/ft_strrchr.c str/ft_strsplit.c str/ft_strstr.c str/ft_strsub.c\
	 str/ft_strtrim.c str/strgen.c
SRCS := $(CHECKS) $(DISPLAY) $(LST) $(MEM) $(MISC) $(STR)
OBJ= ft_isalnum.o ft_isalnumword.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isnumber.o ft_isprint.o\
ft_putchar.o ft_putchar_fd.o ft_putendl.o ft_putendl_fd.o ft_putnbr.o ft_putnbr_fd.o ft_putstr.o ft_putstr_fd.o \
ft_count_lst.o ft_lstadd.o ft_lstaddend.o ft_lstdel.o ft_lstdelone.o ft_lstiter.o ft_lstmap.o ft_lstnew.o lst_add.o \
ft_bzero.o ft_memalloc.o ft_memccpy.o ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memdel.o ft_memmove.o ft_memset.o \
ft_atoi.o ft_itoa.o ft_range.o ft_sqrt.o ft_swap.o ft_tab_size.o ft_tolower.o ft_toupper.o ft_whitespace.o ft_wordtab_to_str.o get_next_line.o \
ft_str_epur.o ft_strcat.o ft_strchr.o ft_strclr.o ft_strcmp.o ft_strcpy.o ft_strcut.o ft_strdel.o ft_strdup.o ft_strequ.o ft_striter.o \
ft_striteri.o ft_strjoin.o ft_strjoin_free.o ft_strjoin_free_one.o ft_strlcat.o ft_strlen.o ft_strmap.o ft_strmapi.o ft_strncat.o \
ft_strncmp.o ft_strncpy.o ft_strnequ.o ft_strnew.o ft_strnstr.o ft_strrchr.o ft_strsplit.o ft_strstr.o ft_strsub.o ft_strtrim.o ft_putnbrendl.o \
strgen.o ft_isspace.o

all: $(NAME)

$(NAME): 
		@$(CC) -c $(FLAGS) $(SRCS) libft.h
		@ar rcs $(NAME) $(OBJ)
clean:
		@rm -rf $(OBJ) libft.h.gch

fclean : clean
		@rm -rf $(NAME)

re: fclean all