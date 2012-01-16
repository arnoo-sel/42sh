##
## Makefile for mysh in /home/jartho_d/42sh/mysh
## 
## Made by adrien1 jarthon
## Login   <jartho_d@epitech.net>
## 
## Started on  Mon May  5 10:13:27 2008 adrien1 jarthon
## Last update Fri Jun 13 15:52:05 2008 arnaud sellier
##

NAME	= 42sh

CC	= `sh get_cc.sh`

OBJ	=	src/*.o \
		src/builtins/*.o \
		src/inhibitors/*.o \
		src/history/*.o \
		src/globing/*.o \
		src/termcaps/*.o \
		src/background/*.o \
		src/completion/*.o

CFLAGS	= -Wall -W $(INCLUDES)

LIBS	= -Llib/ -lmy-`uname -s`-`uname -m` -lvector-`uname -s`-`uname -m` -ltermcap

SAVE	= $(NAME)-save-`date +"%Y:%m:%d-%k-%M"`.tgz
SAVE_DIR= $(HOME)/afs/rendu/c/$(NAME)/

all: $(NAME)

$(NAME): src/*.c src/builtins/*.c src/inhibitors/*.c src/history/*.c src/globing/*.c src/termcaps/*.c  src/background/*.c src/completion/*.c
	@cd src && $(MAKE)
	@echo -n "[32m[build] "
	$(CC) -o $(NAME) $(OBJ) $(LIBS)
	@echo -n "[0m"
clean:
	@cd src && $(MAKE) clean

fclean: clean
	@echo -n "[31m[clean] "
	rm -f $(NAME)
	@echo -n "[0m"

re: fclean all

save:
	@echo "[33m[save] making tgz pakage ... [0m"
	@cd .. && tar -czf $(SAVE) $(NAME)/
	@mkdir -p $(SAVE_DIR)
	@echo "[33m[save] saving on afs ($(SAVE_DIR)) ... [0m"
	@mv ../$(NAME)-save* $(SAVE_DIR)
	@mkdir -p $(HOME)/save/$(NAME)/
	@echo "[33m[save] saving on local disk ($(HOME)/save/$(NAME)/) ... [0m"
	@cp $(SAVE_DIR)* $(HOME)/save/$(NAME)/
