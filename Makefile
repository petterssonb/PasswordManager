PROG = main.exe
SRC = main.cpp passwordManager.cpp
CFLAGS = -g -std=c++20 -Wall -Wno-deprecated-declarations
LIBS = -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto
INCLUDES = -I/opt/homebrew/opt/openssl@3/include
CC = g++

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(LIBS) $(INCLUDES)

clean:
	rm -f $(PROG)

.PHONY: all clean
