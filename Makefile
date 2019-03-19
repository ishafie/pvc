EXE = Main

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC=g++

CPPFLAGS += -Iinclude
CFLAGS += -Wall -std=c++14 -g
LDFLAGS += -std=c++14 -g
LDLIBS +=

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR) $(EXE)
