PROG = main.exe
SRC = main.cpp passwordManager.cpp
CFLAGS = -g -std=c++20 -Wall
LIBS = -lssl -lcrypto
INCLUDES = -I/usr/local/opt/openssl/include
CC = g++

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(LIBS) $(INCLUDES)

clean:
	rm -f $(PROG)

.PHONY: all clean
