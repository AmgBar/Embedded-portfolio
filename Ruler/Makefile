CC = gcc
CCFLAGS = -Wall -pthread
PIGPIOFLAGS = -lpigpio -lrt
SRC = assignment2.c
EXEC = assignment2

build: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CCFLAGS) -o $(EXEC) $(SRC) $(PIGPIOFLAGS)

run: $(EXEC)
	sudo ./$(EXEC)

clean: 
	rm -f $(EXEC)
