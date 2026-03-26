CC = gcc
HEADER = network.h
CFLAGS = -g
BIN_DIR = bin

# prende tutti i file codice
SRCS = $(filter-out network.c, $(wildcard *.c))

# prende i binari
BINS = $(patsubst %.c, $(BIN_DIR)/%, $(SRCS))

all: $(BIN_DIR) $(BINS)

$(BIN_DIR)/%: %.c $(HEADER) network.c
	$(CC) $(CFLAGS) $< network.c -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

print:
	@echo "Sorgenti: $(SRCS)"
	@echo "Destinazioni: $(BINS)"