# Define directories
APP_DIR = app
OBJ_DIR = obj
BIN_DIR = bin

COM = /$(BIN_DIR)/ls

# Define compiler and flags
CXX = g++
CXXFLAGS = -Wall -g


# Find source files and define object and out files
FILES = $(shell find $(APP_DIR) -name "*.cpp")
OBJ_FILES = $(patsubst $(APP_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(FILES))
OUT_FILES = $(patsubst $(APP_DIR)/%.cpp,$(BIN_DIR)/%.out,$(FILES))


# Define targets
all: $(OUT_FILES) $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(APP_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/%.out : $(OBJ_DIR)/%.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

run:
	./$(BIN_DIR)/time.out $(COM)
	./$(BIN_DIR)/stime.out $(COM)
	./$(BIN_DIR)/mtime.out $(COM)

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*.out