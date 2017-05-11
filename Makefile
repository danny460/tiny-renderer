SRC_DIR := src
INC_DIR := include
BIN_DIR := bin
BLD_DIR := build

CC = g++
STD11 = -std=c++11
CFLAGS = -Wall -g -c $(STD11) 
LFLAGS = -Wall -g 
INC := -I$(INC_DIR)

CPP_EXT := .cpp
OBJ_EXT := .o

TARGET := $(BIN_DIR)/renderer
SOURCES := $(shell find $(SRC_DIR) -type f -name "*$(CPP_EXT)")
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BLD_DIR)/%.o , $(SOURCES))

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC) ($LFLAGS) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET)
	@echo "running..."; ./$(TARGET)

$(BLD_DIR)/%$(OBJ_EXT): $(SRC_DIR)/%$(CPP_EXT)
	@mkdir -p $(BLD_DIR)
	@echo " $(CC) $(CFLAGS) $(INC) -o $@ $<"; $(CC) $(CFLAGS) $(INC) -o $@ $<

clean:
	@echo "Cleaning..."; 
	@rm -r $(BLD_DIR)/*$(OBJ_EXT)

.PHONY: clean	