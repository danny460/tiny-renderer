SRC_DIR := src
INC_DIR := include
BIN_DIR := bin
BLD_DIR := build
LIB_DIR := lib

CC = g++
STD11 = -std=c++11
CFLAGS = -Wall -g -c $(STD11) 
LFLAGS = -Wall -g $(STD11)
INC := -I$(INC_DIR)

SRC_EXT := .cpp
OBJ_EXT := .o
DEP_EXT := .h
HPP_EXT := .hpp

TARGET := $(BIN_DIR)/renderer
SOURCES := $(shell find $(SRC_DIR) -type f -name "*$(SRC_EXT)")
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BLD_DIR)/%.o , $(SOURCES))
DEPS := $(shell find $(SRC_DIR) -type f -name "*$(DEP_EXT)")

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET)
	@echo "running..."; ./$(TARGET)

$(BLD_DIR)/%$(OBJ_EXT): $(SRC_DIR)/%$(SRC_EXT)
	@mkdir -p $(BLD_DIR)
	@echo " $(CC) $(CFLAGS) $(INC) -o $@ $<"; $(CC) $(CFLAGS) $(INC) -o $@ $<


clean:
	@echo Cleaning...

console-clear:
	printf '\033c'	

.PHONY: clean	