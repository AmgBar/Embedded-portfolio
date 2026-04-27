CC = gcc

ASSIGNMENT1PIGPIOFLAGS = -Wall -pthread
PIGPIOFLAGS = -lpigpio -lrt

ASSIGNMENT1BFLAGS = 

SRC1 = assignment1pigpio.c
SRC2 = assignment1b.c

EXEC1 = assignment1pigpio
EXEC2 = assignment1b

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(SRC1)
	$(CC) $(ASSIGNMENT1PIGPIOFLAGS) -o $(EXEC1) $(SRC1) $(PIGPIOFLAGS)

$(EXEC2): $(SRC2)
	$(CC) $(ASSIGNMENT1BFLAGS) -o $(EXEC2) $(SRC2)

run1: $(EXEC1)
	sudo ./$(EXEC1)

run2: $(EXEC2)
	sudo ./$(EXEC2)


clean:
	rm -f $(EXEC1) $(EXEC2)