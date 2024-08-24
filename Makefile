# Detect the operating system
ifeq ($(OS), Windows_NT)
    PROG = main.exe
    RM = del
    LIBS = -lssl -lcrypto
    INCLUDES = -Iinclude
else
    PROG = main
    RM = rm -f

    # macOS specific settings
    ifeq ($(shell uname), Darwin)
        LIBS = -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto
        INCLUDES = -I/opt/homebrew/opt/openssl@3/include -Iinclude
    else
    # Linux specific settings
        LIBS = -lssl -lcrypto
        INCLUDES = -Iinclude
    endif
endif

SRC_DIR = src
INC_DIR = include
SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/passwordManager.cpp
CFLAGS = -g -std=c++20 -Wall -Wno-deprecated-declarations $(INCLUDES)
CC = g++
CPPCHECK = cppcheck

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(SRC) $(LIBS)

clean:
	$(RM) $(PROG)

.PHONY: all clean cppcheck

cppcheck:
	@$(CPPCHECK) --quiet --enable=all --error-exitcode=1 \
	--inline-suppr \
	$(SRC)
