CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c99

TARGET = arb_count.exe

SRCS = arb_count.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@powershell -Command "Write-Host 'Cleaning up object files...' -ForegroundColor Yellow"
	del /Q $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) $(TARGET)

re: clean all

.PHONY: all clean re
