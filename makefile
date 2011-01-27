#########################################################
#	Makefile for Pong				#
#		Author : Amirouche HALFAOUI		#
#		Date : 27.10.2010			#
#########################################################

CC = gcc
CFLAGS = -ansi -Wall
LDFLAGS = -lGL -lGLU -lSDL -lSDL_image -lSDL_mixer
EXEC = Pong
DIR_EXEC = bin
DIR_OBJ = obj
DIR_SRC = src
INC = $(wildcard src/includes/*.h)
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)

Debug: all

all: $(DIR_EXEC)/$(EXEC) 

$(DIR_EXEC)/$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(INC)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(DIR_EXEC)/$(EXEC)

mrproper: clean
	rm -f $(DIR_OBJ)/*
