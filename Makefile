PROG = main.exe
SRC = main.cpp passwordManager.cpp
CFLAGS = -g -std=c++20 -Wall
LIBS = 
CC = g++

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(LIBS)

clean:
	rm -f $(PROG)

.PHONY: all clean