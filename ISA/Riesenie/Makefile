CC = gcc
CFLAGS = -g -Wall -Wextra -Werror 
TARGETS = dns


all: $(TARGETS)

dns: dns.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) *.o $(TARGETS)

