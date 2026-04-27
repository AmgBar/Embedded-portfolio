CC=gcc
CFLAGS= -g -I./src 

# Change EXEC value to name and location of executable
# (location is relative to makefile)
EXEC=main
RUNOPTIONS=

SRC_DIR=./src
BIN_DIR=./bin

# To add libraries, add "-l <libname>", for multiple repeat prior for each lib
LIBS = -l pthread -l pigpio -lm
DEPS = 
ARCH = $(shell uname -m)

# Gets all .c files in current directory and src directory
SRC= $(EXEC).c $(wildcard $(SRC_DIR)/*.c)

# Converts the SRC .c files to .o's into the bin directory
OBJ= $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o) 

all: $(BIN_DIR) $(EXEC)

# Creates bin folder
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)  $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


clean:
	rm $(BIN_DIR)/*.o $(EXEC)
	

run: $(EXEC)
	sudo ./$(EXEC) $(RUNOPTIONS)