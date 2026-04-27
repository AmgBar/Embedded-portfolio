CC = gcc
CCFLAGS = -Wall -pthread
PIGPIOFLAGS = -lpigpio -lrt
SRC = assignment3.c
EXEC = assignment3

build: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CCFLAGS) -o $(EXEC) $(SRC) $(PIGPIOFLAGS)
	
run: $(EXEC)
	sudo ./$(EXEC)

clean: 
	rm -f $(EXEC)