# Define directories
APP_DIR = app
OBJ_DIR = obj
BIN_DIR = bin

COM = ls

# Define compiler and flags
CXX = g++
CXXFLAGS = -Wall -g


# Find source files and define object and out files
FILES = $(shell find $(APP_DIR) -name "*.cpp")
OBJ_FILES = $(patsubst $(APP_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(FILES))

# Define targets
all: time stime mtime

time: $(OBJ_DIR)/time.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/time $(OBJ_DIR)/time.o	

stime: $(OBJ_DIR)/stime.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/stime $(OBJ_DIR)/stime.o

mtime: $(OBJ_DIR)/mtime.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/mtime $(OBJ_DIR)/mtime.o

$(OBJ_DIR)/%.o: $(APP_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run:
	./$(BIN_DIR)/time $(COM)
	./$(BIN_DIR)/stime $(COM)
	./$(BIN_DIR)/mtime $(COM)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)