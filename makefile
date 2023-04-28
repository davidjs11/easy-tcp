# macros
HOME    = .

SRC      = $(HOME)/src
EXAMPLES = $(HOME)/examples
INCLUDE  = $(HOME)/include
OBJ      = $(HOME)/obj
LIB      = $(HOME)/lib
BIN      = $(HOME)/bin

all:\
	$(LIB)/libeasyTCP.a\
	echo
	@echo "done!"

examples:\
	echo

echo:\
	$(BIN)/echo-client\
	$(BIN)/echo-server

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

$(BIN)/echo-server:\
	$(OBJ)/echo-server.o\
	$(LIB)/libeasyTCP.a
	@echo "creating echo-server (example) executable..."
	@gcc -o $(BIN)/echo-server\
			$(OBJ)/echo-server.o\
			-L$(LIB)\
			-leasyTCP

$(BIN)/echo-client:\
	$(OBJ)/echo-client.o\
	$(LIB)/libeasyTCP.a
	@echo "creating echo-client (example) executable..."
	@gcc -o $(BIN)/echo-client\
			$(OBJ)/echo-client.o\
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

$(OBJ)/echo-server.o:\
	$(EXAMPLES)/echo-server.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling echo-server (example) program..."
	@gcc -c -o $(OBJ)/echo-server.o\
			   $(EXAMPLES)/echo-server.c\
			 -I$(INCLUDE)

$(OBJ)/echo-client.o:\
	$(EXAMPLES)/echo-client.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling echo-client (example) program..."
	@gcc -c -o $(OBJ)/echo-client.o\
			   $(EXAMPLES)/echo-client.c\
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
