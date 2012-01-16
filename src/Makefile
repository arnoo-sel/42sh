##
## Makefile for mysh in /home/jartho_d/42sh/mysh
## 
## Made by adrien1 jarthon
## Login   <jartho_d@epitech.net>
## 
## Started on  Mon May  5 10:13:27 2008 adrien1 jarthon
## Last update Fri Jun 13 15:52:15 2008 arnaud sellier
##

SRC	=	main.c \
		environ.c \
		path.c \
		quit.c \
		free.c \
		verify_line.c \
		verify_pipeline.c \
		exec_line.c \
		exec_pipeline.c \
		exec_cmd.c \
		signal.c \
		verify_redirect.c \
		verify_pipe_redirless.c \
		extract.c \
		clean_line.c \
		file_handling.c \
		my_getenv.c \
		my_pwd.c \
		catch.c \
		load_conf.c \
		variable.c \
		modif_prompt.c \
		prompt_percent_mod.c \
		main_launch.c \
		tools.c \
		alias_substitution.c

OBJ	= $(SRC:.c=.o)

INCLUDES_FILES	= ../include/*.h

CC	= `sh ../get_cc.sh`

CFLAGS	= -Wall -W -O3 $(INCLUDES)

INCLUDES = -I../include

LIBS	= -L../lib/ -lmy-`uname -s`-`uname -m` -ltermcap

all: $(OBJ)
	@cd background && $(MAKE)
	@cd builtins && $(MAKE)
	@cd history && $(MAKE)
	@cd inhibitors && $(MAKE)
	@cd globing && $(MAKE)
	@cd termcaps && $(MAKE)
	@cd completion && $(MAKE)

$(OBJ): $(INCLUDES_FILES)

.c.o: *.h
	@echo -n "[36m[compi] "
	$(CC) $(CFLAGS) -c $<
	@echo -n "[0m"

clean:
	@cd background && $(MAKE) clean
	@cd builtins && $(MAKE) clean
	@cd inhibitors && $(MAKE) clean
	@cd globing && $(MAKE) clean
	@cd history && $(MAKE) clean
	@cd termcaps && $(MAKE) clean
	@cd completion && $(MAKE) clean
	@echo -n "[31m[clean] "
	rm -f *~ *.o *#
	@echo -n "[0m"

fclean : clean

re: fclean all
