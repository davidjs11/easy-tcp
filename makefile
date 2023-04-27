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


# executables
$(BIN)/server:\
	$(OBJ)/server.o\
	$(LIB)/libeasyTCP.a
	@echo "Creating server executable..."
	@gcc -o $(BIN)/server\
			$(OBJ)/server.o\
			-L$(LIB)\
			-leasyTCP
	@echo

$(BIN)/client:\
	$(OBJ)/client.o\
	$(LIB)/libeasyTCP.a
	@echo "Creating client executable..."
	@gcc -o $(BIN)/client\
			$(OBJ)/client.o\
			-L$(LIB)\
			-leasyTCP

	@echo

# object files
$(OBJ)/server.o:\
	$(SRC)/server.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling server program..."
	@gcc -c -o $(OBJ)/server.o\
			   $(SRC)/server.c\
			 -I$(INCLUDE)
	@echo

$(OBJ)/client.o:\
	$(SRC)/client.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling client program..."
	@gcc -c -o $(OBJ)/client.o\
			   $(SRC)/client.c\
			 -I$(INCLUDE)
	@echo

$(OBJ)/easyTCP.o:\
	$(SRC)/easyTCP.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling easyTCP..."
	@gcc -c -o $(OBJ)/easyTCP.o\
			   $(SRC)/easyTCP.c\
			 -I$(INCLUDE)
	@echo

$(LIB)/libeasyTCP.a:\
	$(OBJ)/easyTCP.o
	@echo "creating easyTCP library..."
	@ar -rvs $(LIB)/libeasyTCP.a\
			 $(OBJ)/easyTCP.o
	@echo


# cleaning
clean:
	@echo "cleaning all..."
	@rm bin/* lib/* obj/*
	@echo
