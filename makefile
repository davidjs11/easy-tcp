### macros ###########################################################
HOME    = .

SRC      = $(HOME)/src
EXAMPLES = $(HOME)/examples
INCLUDE  = $(HOME)/include
OBJ      = $(HOME)/obj
LIB      = $(HOME)/lib
BIN      = $(HOME)/bin


### general rules ####################################################
all:\
	folders\
	lib\
	examples
	@echo "done!"

examples:\
	$(BIN)/echo-client\
	$(BIN)/echo-server\
	$(BIN)/chat-server\
	$(BIN)/chat-client\
	$(BIN)/http
	@echo

lib:\
	$(LIB)/libeasyTCP.a


### creating folders #################################################
folders:\
	$(BIN)/\
	$(LIB)/\
	$(OBJ)/\

$(BIN)/:
	@mkdir bin

$(LIB)/:
	@mkdir lib

$(OBJ)/:
	@mkdir obj

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

$(BIN)/chat-server:\
	$(OBJ)/chat-server.o\
	$(LIB)/libeasyTCP.a
	@echo "creating chat-server executable..."
	@gcc -o $(BIN)/chat-server\
			$(OBJ)/chat-server.o\
			-L$(LIB)\
			-leasyTCP

$(BIN)/chat-client:\
	$(OBJ)/chat-client.o\
	$(LIB)/libeasyTCP.a
	@echo "creating chat-client executable..."
	@gcc -o $(BIN)/chat-client\
			$(OBJ)/chat-client.o\
			-L$(LIB)\
			-leasyTCP -lncurses

$(BIN)/http:\
	$(OBJ)/http.o\
	$(LIB)/libeasyTCP.a
	@echo "creating http server executable..."
	@gcc -o $(BIN)/http\
			$(OBJ)/http.o\
			-L$(LIB)\
			-leasyTCP


### object files #####################################################
$(OBJ)/easyTCP.o:\
	$(SRC)/easyTCP.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling easyTCP..."
	@gcc -c -o $(OBJ)/easyTCP.o\
			   $(SRC)/easyTCP.c\
			 -I$(INCLUDE)

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

$(OBJ)/chat-server.o:\
	$(EXAMPLES)/chat-server.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling chat-server program..."
	@gcc -c -o $(OBJ)/chat-server.o\
			   $(EXAMPLES)/chat-server.c\
			 -I$(INCLUDE)

$(OBJ)/chat-client.o:\
	$(EXAMPLES)/chat-client.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling chat-client program..."
	@gcc -c -o $(OBJ)/chat-client.o\
			   $(EXAMPLES)/chat-client.c\
			 -I$(INCLUDE) -lncurses

$(OBJ)/http.o:\
	$(EXAMPLES)/http.c\
	$(INCLUDE)/easyTCP.h
	@echo "compiling http server program..."
	@gcc -c -o $(OBJ)/http.o\
			   $(EXAMPLES)/http.c\
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
	-rmdir bin lib obj
