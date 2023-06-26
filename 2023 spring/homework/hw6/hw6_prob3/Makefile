export DEBUGINFOD_URLS="https://debuginfod.archlinux.org"

CC=g++
CFLAGS=-Wall -Wextra
CPP_FILES=$(wildcard *.cpp)
HEADER_FILES=$(wildcard *.h)

main: $(CPP_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS) -o $@ $(CPP_FILES)

clean:
	rm -f main