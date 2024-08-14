# Detect the operating system
ifeq ($(OS), Windows_NT)
    PROG = main.exe
    RM = del
    LIBS = -lssl -lcrypto
    INCLUDES =
else
    PROG = main
    RM = rm -f

    # macOS specific settings
    ifeq ($(shell uname), Darwin)
        LIBS = -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto
        INCLUDES = -I/opt/homebrew/opt/openssl@3/include
    else
    # Linux specific settings
        LIBS = -lssl -lcrypto
        INCLUDES =
    endif
endif

SRC = main.cpp passwordManager.cpp
CFLAGS = -g -std=c++20 -Wall -Wno-deprecated-declarations
CC = g++
CPPCHECK = cppcheck

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(SRC) $(LIBS) $(INCLUDES)

clean:
	$(RM) $(PROG)

.PHONY: all clean cppcheck

cppcheck:
	@$(CPPCHECK) --quiet --enable=all --error-exitcode=1 \
	--inline-suppr \
	$(SRC)
