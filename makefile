### macros ###########################################################
HOME    = .

SRC      = $(HOME)/src
EXAMPLES = $(HOME)/examples
INCLUDE  = $(HOME)/include
OBJ      = $(HOME)/obj
LIB      = $(HOME)/lib
BIN      = $(HOME)/bin

all:\
	lib\
	examples
	@echo "done!"

examples:\
	$(BIN)/echo-client\
	$(BIN)/echo-server\
	$(BIN)/http
	@echo

lib:\
	$(LIB)/libeasyTCP.a


### executables ######################################################
$(BIN)/echo-server:\
	$(OBJ)/echo-server.o\
	$(LIB)/libeasyTCP.a
	@echo "creating echo-server executable..."
	@gcc -o $(BIN)/echo-server\
			$(OBJ)/echo-server.o\
			-L$(LIB)\
			-leasyTCP

$(BIN)/echo-client:\
	$(OBJ)/echo-client.o\
	$(LIB)/libeasyTCP.a
	@echo "creating echo-client executable..."
	@gcc -o $(BIN)/echo-client\
			$(OBJ)/echo-client.o\
			-L$(LIB)\
			-leasyTCP

$(BIN)/http:\
	$(OBJ)/http.o\
	$(LIB)/libeasyTCP.a
	@echo "creating http server executable..."
	@gcc -o $(BIN)/http\
			$(OBJ)/http.o\
			-L$(LIB)\
			-leasyTCP


### object files #####################################################
$(OBJ)/echo-server.o:\
	$(EXAMPLES)/echo-server.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling echo-server program..."
	@gcc -c -o $(OBJ)/echo-server.o\
			   $(EXAMPLES)/echo-server.c\
			 -I$(INCLUDE)

$(OBJ)/echo-client.o:\
	$(EXAMPLES)/echo-client.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling echo-client program..."
	@gcc -c -o $(OBJ)/echo-client.o\
			   $(EXAMPLES)/echo-client.c\
			 -I$(INCLUDE)

$(OBJ)/http.o:\
	$(EXAMPLES)/http.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling http server program..."
	@gcc -c -o $(OBJ)/http.o\
			   $(EXAMPLES)/http.c\
			 -I$(INCLUDE)

$(OBJ)/easyTCP.o:\
	$(SRC)/easyTCP.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling easyTCP..."
	@gcc -c -o $(OBJ)/easyTCP.o\
			   $(SRC)/easyTCP.c\
			 -I$(INCLUDE)


### library ##########################################################
$(LIB)/libeasyTCP.a:\
	$(OBJ)/easyTCP.o
	@ar -r $(LIB)/libeasyTCP.a\
			 $(OBJ)/easyTCP.o


### cleaning #########################################################
clean:
	@echo "cleaning all..."
	-rm bin/* lib/* obj/*
