INC_DIR := ../include
BIN_DIR := ../bin
BLD_DIR := ../build
SRC_DIR := ../src

CC = g++
STD11 = -std=c++11
CFLAGS = -Wall -g -c $(STD11) 
LFLAGS = -Wall -g 
INC := -I$(INC_DIR)

CPP_EXT := .cpp
OBJ_EXT := .o

TARGET := $(BIN_DIR)/tester
TESTSRC := geometry.test.cpp
DEPS := $(patsubst %.test$(CPP_EXT), %$(CPP_EXT) , $(TESTSRC))
ALL := $(DEPS) $(TESTSRC) 
OBJECTS := $(patsubst %$(CPP_EXT), $(BLD_DIR)/%$(OBJ_EXT) , $(ALL))

$(TARGET): $(OBJECTS)
	@printf "\033c"
	@echo "Linking.."
	@echo "$(CC) $(LFLAGS) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET)
	@echo "Cleaning..."; rm -r $(OBJECTS) 
	@echo "Running..."; ./$(TARGET)

$(BLD_DIR)/%.test$(OBJ_EXT): %.test$(CPP_EXT)
	@mkdir -p $(BLD_DIR)
	@echo " $(CC) $(CFLAGS) $(INC) -o $@ $<"; $(CC) $(CFLAGS) $(INC) -o $@ $<

$(BLD_DIR)/%$(OBJ_EXT): $(SRC_DIR)/%$(CPP_EXT)
	@mkdir -p $(BLD_DIR)
	@echo " $(CC) $(CFLAGS) $(INC) -o $@ $<"; $(CC) $(CFLAGS) $(INC) -o $@ $<

		