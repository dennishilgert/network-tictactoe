CC = gcc -Wall
ObjectFiles = main.o communicator.o logic.o
Program = game

$(Program): $(ObjectFiles)
	$(CC) -o $@ $^

$(ObjectFiles):
	$(CC) -c $<

main.o: main.c main.h

communicator.o: communicator.c communicator.h

logic.o: logic.c logic.h

clean:
	rm *.o game

run:
	./$(Program)