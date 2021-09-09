NAME := minitalk_server minitalk_client

CFLAGS ?= -Wall -Werror -Wextra
ifdef DEBUG
CFLAGS := -g $(CFLAGS)
endif
O_SERVER := minitalk_server.o
O_SERVER := $(addprefix obj/,$(O_SERVER))
O_CLIENT := minitalk_client.o
O_CLIENT := $(addprefix obj/,$(O_CLIENT))
HEADER_FILES := minitalk_client.h minitalk.h
HEADER_FILES := $(addprefix headers/,$(HEADER_FILES))

all: $(NAME)

$(word 1, $(NAME)): $(O_SERVER)
	$(MAKE) bonus -C ./ft_printf
	@echo "[minitalk] compiling minitalk server"
	@$(CC) $(CFLAGS) $(O_SERVER) ft_printf/libftprintf.a -o $(word 1, $(NAME))

$(word 2, $(NAME)): $(O_CLIENT)
	$(MAKE) bonus -C ./ft_printf
	@echo "[minitalk] compiling minitalk client"
	@$(CC) $(CFLAGS) $(O_CLIENT) ft_printf/libftprintf.a -o $(word 2, $(NAME))

obj/%.o: src/%.c $(HEADER_FILES)
	@mkdir -p obj
	@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean:
	@echo "[minitalk] cleaning minitalk"
	$(MAKE) clean -C ./ft_printf
	@rm -f $(O_SERVER)
	@rm -f $(O_CLIENT)
	@rmdir obj

fclean: clean
	@echo "[minitalk] fully cleaning minitalk"
	$(MAKE) fclean -C ./ft_printf
	@rm -f $(NAME)

re: fclean all

bonus: all

run: all
	@echo "[minitalk] running minitalk"
	./$(word 1, $(NAME))

debug:
	$(MAKE) DEBUG=1

.PHONY: all clean fclean re bonus run debug
