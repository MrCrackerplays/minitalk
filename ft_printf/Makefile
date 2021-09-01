NAME = libftprintf.a
OBJ_FILES = ft_printf.o flags.o field_width.o precision.o specifier.o \
	parse_specifier_s.o parse_specifier_c.o parse_specifier_d.o \
	parse_specifier_i.o parse_specifier_percent.o parse_specifier_x.o \
	parse_specifier_u.o parse_specifier_p.o itob.o parse_specifier_o.o \
	length_modifier.o parse_specifier_n.o
HEADER_FILES = ft_printf.h
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(MAKE) bonus -C ./libft
	cp libft/libft.a $(NAME)
	ar -rcs $(NAME) $(OBJ_FILES)

%.o: %.c $(HEADER_FILES)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(MAKE) clean -C ./libft
	rm -f $(OBJ_FILES)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
