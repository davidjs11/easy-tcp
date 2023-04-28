# macros
HOME	= .

SRC		= $(HOME)/src
INCLUDE	= $(HOME)/include
OBJ		= $(HOME)/obj
LIB		= $(HOME)/lib
BIN		= $(HOME)/bin

all:\
	$(LIB)/libeasyTCP.a\
	$(BIN)/server\
	$(BIN)/client
	@echo "done!"


# executables
$(BIN)/server:\
	$(OBJ)/server.o\
	$(LIB)/libeasyTCP.a
	@echo "creating server executable..."
	@gcc -o $(BIN)/server\
			$(OBJ)/server.o\
			-L$(LIB)\
			-leasyTCP

$(BIN)/client:\
	$(OBJ)/client.o\
	$(LIB)/libeasyTCP.a
	@echo "creating client executable..."
	@gcc -o $(BIN)/client\
			$(OBJ)/client.o\
			-L$(LIB)\
			-leasyTCP


# object files
$(OBJ)/server.o:\
	$(SRC)/server.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling server program..."
	@gcc -c -o $(OBJ)/server.o\
			   $(SRC)/server.c\
			 -I$(INCLUDE)

$(OBJ)/client.o:\
	$(SRC)/client.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling client program..."
	@gcc -c -o $(OBJ)/client.o\
			   $(SRC)/client.c\
			 -I$(INCLUDE)

$(OBJ)/easyTCP.o:\
	$(SRC)/easyTCP.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling easyTCP..."
	@gcc -c -o $(OBJ)/easyTCP.o\
			   $(SRC)/easyTCP.c\
			 -I$(INCLUDE)


# library
$(LIB)/libeasyTCP.a:\
	$(OBJ)/easyTCP.o
	@ar -r $(LIB)/libeasyTCP.a\
			 $(OBJ)/easyTCP.o


# cleaning
clean:
	@echo "cleaning all..."
	@rm bin/* lib/* obj/*
