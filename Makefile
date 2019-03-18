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

all: Main

Main: Main.o Glouton.o bruteforce.o Genetic.o Graph.o
	$(CC) $(LDFLAGS) $(LDLIBS) Main.o Glouton.o bruteforce.o Genetic.o Graph.o -o $@

Main.o: $(SRC_DIR)/Main.cpp $(SRC_DIR)/Graph.h $(SRC_DIR)/Glouton.h $(SRC_DIR)/Algo.h $(SRC_DIR)/Genetic.h $(SRC_DIR)/bruteforce.h $(SRC_DIR)/pvc.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SRC_DIR)/Main.cpp

Graph.o: $(SRC_DIR)/Graph.cpp $(SRC_DIR)/Graph.h $(SRC_DIR)/pvc.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SRC_DIR)/Graph.cpp
	
Genetic.o:  $(SRC_DIR)/Genetic.cpp $(SRC_DIR)/Algo.h $(SRC_DIR)/Glouton.h $(SRC_DIR)/pvc.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SRC_DIR)/Genetic.cpp

bruteforce.o: $(SRC_DIR)/bruteforce.cpp $(SRC_DIR)/bruteforce.h $(SRC_DIR)/Algo.h $(SRC_DIR)/pvc.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SRC_DIR)/bruteforce.cpp

Glouton.o: $(SRC_DIR)/Glouton.cpp $(SRC_DIR)/Glouton.h $(SRC_DIR)/Algo.h $(SRC_DIR)/pvc.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SRC_DIR)/Glouton.cpp

	
clean:
	$(RM) $(OBJ_DIR) $(EXE)
