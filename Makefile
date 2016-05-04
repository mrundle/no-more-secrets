BIN=bin
OBJ=obj
SRC=src

CC = gcc
CFLAGS = -Wextra -Wall
LDLIBS = -lncurses
NCURSES_H = /usr/include/ncurses.h

OBJS = \
	$(OBJ)/nms.o        \
	$(OBJ)/screen_buf.o
	
all: $(BIN)/nms $(BIN)/sneakers

$(BIN)/nms: $(OBJ)/main.o $(OBJS) | $(BIN)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(BIN)/sneakers: $(OBJ)/sneakers.o $(OBJS)  | $(BIN)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ) $(NCURSES_H)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)

$(NCURSES_H):
	sudo apt-get update
	sudo apt-get install ncurses-dev

clean:
	rm -rf $(BIN)
	rm -rf $(OBJ)
