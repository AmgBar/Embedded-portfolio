CC = gcc
CCFLAGS = -Wall -l pthread
PIGPIOFLAGS = -lpigpio -lrt
SRC = followLine.c
EXEC = followLine

build: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CCFLAGS) -o $(EXEC) $(SRC) $(PIGPIOFLAGS)

run: $(EXEC)
	sudo ./$(EXEC)

clean: 
	rm -f $(EXEC)